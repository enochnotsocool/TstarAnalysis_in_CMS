/*******************************************************************************
 *
 *  Filename    : DataToMCBackGround.cc
 *  Description : Comparing Data to MC background.
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TLegend.h"
#include "TLine.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

//------------------------------------------------------------------------------ 
//   Defining font size
//------------------------------------------------------------------------------
#define AXIS_LABEL_SIZE 10
#define AXIS_TITLE_SIZE 10

static TH1F* dataHist;
static TH1F* tempHist;
static float tempScale;

//------------------------------------------------------------------------------ 
//   Public method implementation
//------------------------------------------------------------------------------
void CombineMgr::makeDataToBGPlot( const PlotName& target )
{
   std::string targetName=Stringify( target );
   printf( "making plot %s\n" , targetName.c_str() );
   _stackHist = new THStack( (targetName+"sh").c_str() , (makeHistTitle(target)).c_str() );
   _canvas    = new TCanvas( (targetName+"c").c_str() , targetName.c_str() );
   initTotalHist( target );

   //----- Preparing MC  -----------------------------------------------------------
   for( const auto& pair : _MCbackgroundMap ) {
      addMCToStack( pair.second , target ); }
   setCombinedTotalErrors();

   //----- Plotting Histograms   --------------------------------------------------
   TPad* pad1 = new TPad( "pad1" , "pad1" , 0 , 0.3025 , 1., 1.0 );
   pad1->SetBottomMargin(0.025);
   pad1->Draw();
   pad1->cd();
   dataHist = (TH1F*)_dataSample->Hist(target)->Clone();
   float y_max = 1.2* std::max( dataHist->GetMaximum() , _stackHist->GetMaximum() );
   dataHist->SetMaximum( y_max );
   _stackHist->SetMaximum( y_max );
   _stackHist->Draw("hist");
   _totalHist->Draw("same E2");
   dataHist->SetStats(0);
   _totalHist->GetXaxis()->SetLabelSize(0);
   _totalHist->GetXaxis()->SetTitleSize(0);
   _stackHist->GetXaxis()->SetLabelSize(0);
   _stackHist->GetXaxis()->SetTitleSize(0);
   dataHist->GetXaxis()->SetLabelSize(0);
   dataHist->GetXaxis()->SetTitleSize(0);

   _totalHist->GetYaxis()->SetTitleFont(43);
   _stackHist->GetYaxis()->SetTitleFont(43);
   dataHist->GetYaxis()->SetTitleFont(43);
   _totalHist->GetYaxis()->SetLabelFont(43);
   _stackHist->GetYaxis()->SetLabelFont(43);
   dataHist->GetYaxis()->SetLabelFont(43);
   _totalHist->GetYaxis()->SetTitleSize( AXIS_TITLE_SIZE );
   _totalHist->GetYaxis()->SetLabelSize( AXIS_LABEL_SIZE );
   _stackHist->GetYaxis()->SetTitleSize( AXIS_TITLE_SIZE );
   _stackHist->GetYaxis()->SetLabelSize( AXIS_LABEL_SIZE );
   dataHist->GetYaxis()->SetLabelSize( AXIS_LABEL_SIZE );
   dataHist->GetYaxis()->SetTitleSize( AXIS_TITLE_SIZE );
   dataHist->Draw("same axis");
   dataHist->Draw("SAME LPE1");
   makeCombinedLegend( target );
   _combineLegend->Draw();
   _canvas->cd();

   //----- Plotting comparison plot  ----------------------------------------------
   TPad*   pad2 = new TPad( "pad2" , "pad2" , 0 , 0.05, 1, 0.2975 );
   TLine*  l    = new TLine( dataHist->GetXaxis()->GetXmin(), 0.0 , dataHist->GetXaxis()->GetXmax() , 0.0 );
   setCombinedRelativeErrors();
   l->SetLineColor(kRed);
   pad2->SetTopMargin(0.025);
   pad2->SetBottomMargin(0.2);
   pad2->Draw();
   pad2->cd();
   TH1F* dataRatio = (TH1F*)dataHist->Clone();
   dataRatio->SetStats(0);
   dataRatio->Add( _totalHist , -1 );
   dataRatio->Divide( _totalHist );
   dataRatio->SetMaximum( +1.0 );
   dataRatio->SetMinimum( -1.0 );
   dataRatio->SetTitle("");
   dataRatio->GetYaxis()->SetTitle("#frac{Data-MC}{MC}");
   dataRatio->GetYaxis()->SetNdivisions( 405 );
   dataRatio->GetYaxis()->SetTitleOffset(1.5);
   dataRatio->GetYaxis()->SetTitleFont(43);
   dataRatio->GetYaxis()->SetLabelFont(43);
   dataRatio->GetYaxis()->SetTitleSize( AXIS_TITLE_SIZE );
   dataRatio->GetYaxis()->SetLabelSize( AXIS_LABEL_SIZE );
   dataRatio->GetXaxis()->SetTitleOffset(4.5);
   dataRatio->GetXaxis()->SetTitleFont(43);
   dataRatio->GetXaxis()->SetLabelFont(43);
   dataRatio->GetXaxis()->SetTitleSize( AXIS_TITLE_SIZE );
   dataRatio->GetXaxis()->SetLabelSize( AXIS_LABEL_SIZE );
   dataRatio->Draw("ep");
   dataRatio->Draw("same axis");
   _relErrHist->Draw("same e2");
   l->Draw("same");
   _canvas->cd();


   //----- Cleaning up  -----------------------------------------------------------
   printf("Writing to file....");
   _canvas->Write();
   delete _stackHist;
   delete _canvas;
   delete _totalHist;
   delete _combineLegend;
   //delete pad1;
   //delete pad2;
   printf("Done!\n");
}

//------------------------------------------------------------------------------ 
//   Private helper function implementation
//------------------------------------------------------------------------------
const std::string CombineMgr::makeHistTitle( const PlotName& target ) const 
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

void CombineMgr::addMCToStack( SampleMgr* sample, const PlotName& target )
{
   tempHist = (TH1F*)( sample->Hist( target )->Clone() );
   if( tempHist->Integral() == 0 ){ 
      std::cerr << "Warning Skipping over empty data set: " << sample->name() << std::endl ;
      return ;
   }
   tempScale = getHistScale( sample );
   tempHist->Scale( tempScale ) ; 
   _stackHist->Add( tempHist );
   _totalHist->Add( tempHist );
   
   printf( "Plotting sample %s, scaling from %f to %f events\n",
         (sample->NameString()).c_str() ,
         sample->getRawEventCount() ,
         sample->getRawEventCount()*tempScale );
}

float CombineMgr::getHistScale( SampleMgr* sample ) const 
{
   float ans = sample->getExpectedYield(_totalLumi).CentralValue();
   ans /= sample->getRawEventCount();
   return ans;
}

void CombineMgr::initTotalHist( const PlotName& target ) 
{
   _totalHist = new TH1F( (Stringify(target)+"h").c_str() , (makeHistTitle(target)).c_str() ,
         availiablePlots[target].BinCount() , availiablePlots[target].XMin() , availiablePlots[target].XMax() );
   _totalHist->SetFillStyle(3004);
   _totalHist->SetFillColor(1);
}

void CombineMgr::makeCombinedLegend( const PlotName& target )
{
   _combineLegend = new TLegend( 0.75 , 0.75 , 0.95 , 0.95 );
   _combineLegend->AddEntry( _MCsignalMap[Tstar_M1000]->Hist(target) , "t^{*} signal" , "f" );
   _combineLegend->AddEntry( _MCbackgroundMap[TTJets]->Hist(target) , "t#bar{t} + Jets ", "f");
   _combineLegend->AddEntry( _MCbackgroundMap[SingleT_S]->Hist(target) , "Single top" , "f" );
   _combineLegend->AddEntry( _MCbackgroundMap[WJets]->Hist(target) , "Bosons" , "f" );
   _combineLegend->AddEntry( _MCbackgroundMap[TTW_Lepton]->Hist(target) , "t#bar{t} + Boson" , "f" );
   _combineLegend->AddEntry( _totalHist , "Error" , "f" );
   _combineLegend->AddEntry( _dataSample->Hist(target) , "Data" , "lp" );
}

void CombineMgr::setCombinedTotalErrors()
{
   Parameter total_background;
   float     avgError;
   float     binContent;
   float     binError;
   for( const auto& pair : _MCbackgroundMap ){
      total_background += pair.second->getExpectedYield( _totalLumi );
   }
   avgError = ( total_background.RelativeLowerError() + total_background.RelativeUpperError() );
   for( int i = 1 ; i < _totalHist->GetSize()-1 ; ++i ){
      binContent = _totalHist->GetBinContent(i);
      binError   = _totalHist->GetBinError(i);
      binError   += binContent*avgError;
      _totalHist->SetBinError( i , binError );
   }
}

void CombineMgr::setCombinedRelativeErrors()
{
   float originalBinContent;
   float originalError;
   _relErrHist = (TH1F*)_totalHist->Clone();
   for( int i = 0 ; i < _relErrHist->GetSize()-1; ++i ){
      originalBinContent = _relErrHist->GetBinContent(i);
      originalError      = _relErrHist->GetBinError(i);
      originalError     += dataHist->GetBinError(i);
      _relErrHist->SetBinContent( i, 0.0 );
      _relErrHist->SetBinError( i , originalError/originalBinContent ); 
   }
}
