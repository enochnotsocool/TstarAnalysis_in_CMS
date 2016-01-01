/*******************************************************************************
 *
 *  Filename    : DataToMCBackGround.cc
 *  Description : Comparing Data to MC background.
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include "TLegend.h"
#include "TLine.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

//------------------------------------------------------------------------------ 
//   Public method implementation
//------------------------------------------------------------------------------
void ChannelMgr::MakeDataToBGPlot( const PlotName& target )
{
   if( !CheckPlotName( target ) ) {
      cerr << "Error: Plot " << Stringify(target) << "not avaliable" << endl;
      return;
   }

   // Declaring Helper variables;
   const string   targetName = Stringify( target );
   const string   histName   = makeHistTitle(target);
   const PlotDef& def        = availiablePlots[target];
   const unsigned bins       = def.BinCount();
   const double   xmin       = def.XMin();
   const double   xmax       = def.XMax();
   printf( "making plot %s\n" , targetName.c_str() );

   // Declaring Plots entities 
   TFile* plotfile = openPlotFile();
   TCanvas* canvas    = new TCanvas( (targetName+"c").c_str() , targetName.c_str() );
   THStack* bg_stack  = new THStack( (targetName+"_stack").c_str() , histName.c_str() );
   TH1F*    totError  = new TH1F( (targetName+"tot_err").c_str(), histName.c_str(), bins, xmin, xmax );
   TH1F*    data      = (TH1F*)_dataSample->Hist(target)->Clone();
   TH1F*    relError  = NULL;//Generated in functions makeBGStack()
   TH1F*    dataRatio = NULL;//Generating in function makeDataBGRatio()
   TLegend* combineLegend = new TLegend( 0.75 , 0.75 , 0.95 , 0.95 );
   TLine*  l              = new TLine( xmin , 0.0 , xmax , 0.0 );

   //----- Preparing MC  -----------------------------------------------------------
   makeBGStack( bg_stack, totError, relError ,target );
   makeCombinedLegend( combineLegend, totError, target );
   makeDataBGRatio( dataRatio, data, totError );
   matchHeights( data, totError );

   //----- Making Total Plot  -----------------------------------------------------
   TPad* pad1 = new TPad( "pad1" , "pad1" , 0 , 0.3025 , 1., 1.0 );
   pad1->SetBottomMargin(0.025);
   pad1->Draw();
   pad1->cd();
   
   //Drawing
   bg_stack->Draw("hist");
   totError->Draw("same E2");
   data->Draw("same axis");
   data->Draw("same LPE1");
   combineLegend->Draw();
   canvas->cd();

   //----- Making relative plot  --------------------------------------------------
   TPad*   pad2 = new TPad( "pad2" , "pad2" , 0 , 0.05, 1, 0.2975 );
   l->SetLineColor(kRed);
   pad2->SetTopMargin(0.025);
   pad2->SetBottomMargin(0.2);
   pad2->Draw();
   pad2->cd();
   dataRatio->Draw("ep");
   dataRatio->Draw("same axis");
   relError->Draw("same e2");
   l->Draw("same");
   canvas->cd();

   //----- Cleaning up  -----------------------------------------------------------
   printf("Writing to file....");
   canvas->Write();
   delete bg_stack;
   delete totError;
   delete relError;
   delete combineLegend;
   delete pad1;
   delete pad2;
   delete canvas;
   delete l;

   plotfile->Close();
   delete plotfile;
   printf("Done!\n");
}

//------------------------------------------------------------------------------ 
//   Private helper function implementation
//------------------------------------------------------------------------------
void ChannelMgr::makeBGStack( THStack*& stack, TH1F*& total, TH1F*& rel, const PlotName& target ) const
{
   const SampleMgr* sample;
   TH1F*     tempHist;
   float     tempScale;
   Parameter bgCount ;

   for( const auto& pair : _MCbackgroundMap ) {
      sample = pair.second;
      tempHist = (TH1F*)( sample->Hist( target )->Clone() );
      if( tempHist->Integral() == 0 ){ 
         std::cerr << "Warning Skipping over empty data set: " << sample->NameString() << std::endl ;
         continue ;
      }
      tempScale = getHistScale( sample );
      tempHist->Scale( tempScale ) ; 
      stack->Add( tempHist );
      total->Add( tempHist );
      bgCount += pair.second->getExpectedYield( _totalLumi );
      
      printf( "Plotting sample %s, scaling from %f to %f events\n",
            (sample->NameString()).c_str() ,
            sample->getRawEventCount() ,
            sample->getRawEventCount()*tempScale );
   }
   
   //----- Correcting total histogram to include systematics  ---------------------
   float     avgError = bgCount.RelativeAvgError();
   float     binContent;
   float     binError;
   rel = (TH1F*) total->Clone();
   for( int i = 1 ; i < total->GetSize()-1 ; ++i ){
      binContent = total->GetBinContent(i);
      binError   = total->GetBinError(i);
      binError   += binContent*avgError;
      
      total->SetBinError( i , binError );
      rel->SetBinContent( i, 0.0 );
      rel->SetBinError( i , binError/binContent ); 
   }
   // Default styling
   cout << "Setting style for THStack" << endl;
   //setFontStyle( stack ); 
   cout << "Setting style for total error hist" << endl;
   setFontStyle( total ); 
   // Additional styling 
   total->SetFillStyle(3004);
   total->SetFillColor(1);
   rel->SetFillStyle(3004);
   total->SetFillColor(1);
}

void ChannelMgr::makeDataBGRatio( TH1F*& ratio, const TH1F* data, const TH1F* bg ) const
{
   ratio = (TH1F*)data->Clone();
   ratio->Add( bg , -1 );
   ratio->Divide( bg );
   ratio->SetMaximum( +1.0 );
   ratio->SetMinimum( -1.0 );
   ratio->SetTitle("");
   ratio->GetYaxis()->SetTitle("#frac{Data-MC}{MC}");

   // Styling
   setFontStyle( ratio );
   setXAxisFont( ratio );
   ratio->GetYaxis()->SetNdivisions( 405 );
   ratio->GetYaxis()->SetTitleOffset(1.5);
   ratio->GetXaxis()->SetTitleOffset(4.5);
}

const std::string ChannelMgr::makeHistTitle( const PlotName& target ) const 
{
   std::string xtitle;
   std::string ytitle;
   std::string title;
   
   title  = availiablePlots[target].Title();
   xtitle = availiablePlots[target].Xtitle();
   ytitle = availiablePlots[target].Ytitle();
   title  = title +";" + xtitle + ";" + ytitle ;
   return title;
}

float ChannelMgr::getHistScale( const SampleMgr* sample ) const 
{
   float ans = sample->getExpectedYield(_totalLumi).CentralValue();
   ans /= sample->getRawEventCount();
   return ans;
}

void ChannelMgr::makeCombinedLegend( TLegend* x, const TH1F* err, const PlotName& target )
{
   x->AddEntry( _MCsignalMap[Tstar_M1000]->Hist(target) , "t^{*} signal" , "f" );
   x->AddEntry( _MCbackgroundMap[TTJets]->Hist(target) , "t#bar{t} + Jets ", "f");
   x->AddEntry( _MCbackgroundMap[SingleT_S]->Hist(target) , "Single top" , "f" );
   x->AddEntry( _MCbackgroundMap[WJets]->Hist(target) , "Bosons" , "f" );
   x->AddEntry( _MCbackgroundMap[TTW_Lepton]->Hist(target) , "t#bar{t} + Boson" , "f" );
   x->AddEntry( err , "Error" , "f" );
   x->AddEntry( _dataSample->Hist(target) , "Data" , "lp" );
}

