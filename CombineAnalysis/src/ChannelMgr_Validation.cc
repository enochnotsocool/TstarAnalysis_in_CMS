/*******************************************************************************
 *
 *  Filename    : DataToMCBackGround.cc
 *  Description : Comparing Data to MC background.
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"

#include "CMSSW_Utils/Utils_Functions/interface/Utils_ROOT.h"
#include "TLegend.h"
#include "TLine.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

//------------------------------------------------------------------------------ 
//   Public method implementation
//------------------------------------------------------------------------------
void ChannelMgr::MakeDataBGPlot( const string& target ) const
{
   if( !availablePlots.HasHistogram(target) ) {
      cerr << "Error: Plot " << target << "not available" << endl;
      return;
   }

   // Declaring Helper variables;
   const string   savepath   = PlotFilePath( "Data_v_BG_" + target );
   const string   histName   = availablePlots[target].MakeHistTitle();
   const unsigned bins       = availablePlots[target].BinCount(); 
   const double   xmin       = availablePlots[target].XMin();
   const double   xmax       = availablePlots[target].XMax();
   cout << "Making plot" << target.c_str() << " " << bins << " " << xmax << " " << xmin << endl;

   // Declaring Plots entities 
   TCanvas* canvas        = new TCanvas( (target+"c").c_str() , target.c_str(), 1600,1000 );
   THStack* bg_stack      = new THStack( (target+"_stack").c_str() , histName.c_str() );
   TH1F*    totError      = new TH1F   ( (target+"_terr").c_str(), histName.c_str(), bins, xmin, xmax );
   TH1F*    data          = (TH1F*)_dataSample.Hist(target)->Clone();
   TH1F*    relError      = NULL;//Generated in functions makeBGStack()
   TH1F*    dataRatio     = NULL;//Generating in function makeDataBGRatio()
   TLegend* combineLegend = new TLegend( 0.75 , 0.55 , 0.95 , 0.95 );
   TLine*  l              = new TLine( xmin , 0.0 , xmax , 0.0 );

   //----- Preparing MC  -----------------------------------------------------------
   MakeBGStack( bg_stack, totError, relError ,target );
   MakeCombinedLegend( combineLegend, totError, target );
   MatchHeights( data, totError );
   
   TPad* pad1 = new TPad( "pad1" , "pad1" , 0 , 0.3025 , 1., 1.0 );
   pad1->SetBottomMargin(0.025);
   pad1->Draw();
   pad1->cd();
   
   bg_stack->Draw("hist");
   data->Draw("same axis");
   data->Draw("same LPE1");
   totError->Draw("same E2");
   combineLegend->Draw();

   // Additional styling
   HideXAxis(data);
   HideXAxis(totError);
   data->SetMarkerStyle(21);
   data->SetLineColor(kBlack);
   totError->SetFillColor(kBlack);
   totError->SetLineColor(kBlack);
   totError->SetFillStyle(3004);
   bg_stack->GetXaxis()->SetLabelSize(0);
   bg_stack->GetXaxis()->SetTitleSize(0);
   canvas->cd();

   //----- Making relative plot  --------------------------------------------------
   MakeDataBGRatio( dataRatio, data, totError );
   l->SetLineColor(kRed);
   TPad*   pad2 = new TPad( "pad2" , "pad2" , 0 , 0.05, 1, 0.2975 );
   pad2->SetTopMargin(0.025);
   pad2->SetBottomMargin(0.2);
   pad2->Draw();
   pad2->cd();

   dataRatio->Draw("ep");
   relError->Draw("same axis");
   relError->Draw("same e2");
   l->Draw("same");

   //Additional styling 
   dataRatio->GetXaxis()->SetLabelSize(16);
   dataRatio->GetXaxis()->SetTitleSize(16);
   relError->SetFillColor(kBlack);
   relError->SetFillStyle(3004);
   relError->SetStats(0);
   canvas->cd();

   //----- Save and clean up  -----------------------------------------------------
   printf("Writing to file....");
   canvas->SaveAs( savepath.c_str() );
   delete bg_stack;
   delete totError;
   delete relError;
   delete combineLegend;
   delete pad1;
   delete pad2;
   delete canvas;
   delete l;
   printf("Done!\n");
}

void ChannelMgr::MakeSignalPlot( const std::string& ) const
{}

//------------------------------------------------------------------------------ 
//   Private helper function implementation
//------------------------------------------------------------------------------
void ChannelMgr::MakeBGStack( THStack*& stack, TH1F*& total, TH1F*& rel, const std::string& target ) const
{
   TH1F*     tempHist;
   Parameter bgCount ;

   //----- Making stack  ----------------------------------------------------------
   for( auto it = _MCSampleTable.rbegin() ; it != _MCSampleTable.rend(); ++it ){   
      const auto& list = (*it);
      if( list.Name() == "Signal" ) { continue; }
      for( const auto& sample : list){
         tempHist = (TH1F*)( sample.Hist(target)->Clone() );
         if( tempHist->Integral() == 0 ){ 
            std::cerr << "Warning Skipping over empty data set: " << sample.Name() << std::endl ;
            continue ;
         }
         tempHist->Scale( sample.GetHistogramScale(_totalLumi) ) ; 
         stack->Add( tempHist );
         total->Add( tempHist );
         bgCount += sample.ExpectedYield( _totalLumi );
      }
   }

   //----- Correcting statistical error  ------------------------------------------
   double avgError = bgCount.RelativeAvgError();
   double binContent;
   double binError;
   rel = (TH1F*) total->Clone();
   for( int i = 1 ; i < total->GetSize()-1 ; ++i ){
      binContent = total->GetBinContent(i);
      binError   = total->GetBinError(i);
      binError   += binContent*avgError;

      total->SetBinError( i , binError );
      rel->SetBinContent( i, 0.0 );
      rel->SetBinError( i , binError/binContent ); 
   }

}

void ChannelMgr::MakeDataBGRatio( TH1F*& ratio, const TH1F* data, const TH1F* bg ) const
{
   ratio = (TH1F*)data->Clone();
   ratio->Add( bg , -1 );
   ratio->Divide( bg );
   ratio->SetMaximum( +1.0 );
   ratio->SetMinimum( -1.0 );
   ratio->SetTitle("");
   ratio->GetYaxis()->SetTitle("#frac{Data-MC}{MC}");

   ratio->GetYaxis()->SetNdivisions( 405 );
   ratio->GetYaxis()->SetTitleOffset(1.0);
   ratio->GetXaxis()->SetTitleOffset(4.5);
}


void ChannelMgr::MakeCombinedLegend( TLegend* x, const TH1F* err, const std::string& target ) const
{
   x->AddEntry( (TObject*)NULL , "" , "" );
   for( const auto& list : _MCSampleTable ){
      if( list.Name() == "Signal" ) { continue; }
      x->AddEntry( list.front().Hist(target) , list.RootName().c_str() , "f" ); 
   }
   x->AddEntry( err , "Error" , "f" );
   x->AddEntry( _dataSample.Hist(target) , "Data" , "lp" );
}

