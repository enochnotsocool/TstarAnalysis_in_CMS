/*******************************************************************************
 *
 *  Filename    : PlotCreate.cc
 *  Description : Implementation for plot merging
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "AnalysisMgr.h"
#include "TLegend.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
//------------------------------------------------------------------------------ 
//   Helper variables
//------------------------------------------------------------------------------
static TCanvas*  canvas;
static THStack*  stackHist;
static SampleInfo* tempSample;
static TH1F*       tempHist;
static TH1F*       dataHist;
static TLegend*    legend;
static float       tempScale;
static std::string xtitle;
static std::string ytitle;
static std::string title;

//------------------------------------------------------------------------------ 
//   Helper functions
//------------------------------------------------------------------------------
void makeTitle( const std::string& );

void AnalysisMgr::makePlot( const std::string& target )
{
   makeTitle(target);
   printf( "making plot %s\n" , target.c_str() );
   stackHist = new THStack( (target+"sh").c_str() , title.c_str() );
   canvas    = new TCanvas( (target+"c").c_str() , target.c_str() );

   
   //----- Preparing MC  -----------------------------------------------------------
   for( const auto& pair : _sampleMap ) {
      if( pair.first == "Data" ) continue;  // Skipping data
      tempSample  = pair.second ; 
      tempHist    = (TH1F*)(tempSample->Hist( target )->Clone());
      if( tempHist->Integral() == 0 ){ 
         std::cerr << "Warning Skipping over empty data set" << std::endl ;
         continue ;
      }

      tempScale   = _totalLumi * tempSample->crossSection() ;
      tempScale  *= tempSample->selectionEff();
      printf( "Plotting sample %s with %f events\n", pair.first.c_str(), tempScale );
      tempScale  /= tempHist->Integral();
      tempHist->Scale( tempScale ) ; 
      stackHist->Add( tempHist ); 
   }
   //----- Plotting data  ---------------------------------------------------------
   if( ! sample("Data") ){
      std::cerr << "Warning! Data sample not found!" << std::endl; 
   } else {
      dataHist = (TH1F*)sample("Data")->Hist(target)->Clone();
      float y_max = 1.2* std::max( dataHist->GetMaximum() , stackHist->GetMaximum() );
      dataHist->SetMaximum( y_max );
      stackHist->SetMaximum( y_max );
      stackHist->Draw("hist");
      //stackHist->Draw("same axis");
      dataHist->SetStats(0);
      dataHist->Draw("same axis");
      dataHist->Draw("SAME LPE1");
   }

   //----- Setting up Legends  ----------------------------------------------------
   legend = new TLegend(0.75, 0.75, .95, .95);
   legend->AddEntry( _sampleMap["Tstar"]->Hist(target) , "t^{*}#rightarrow tg" , "f" );
   legend->AddEntry( _sampleMap["SingleTop_Schannel"]->Hist(target) , "Single t" , "f" );
   legend->AddEntry( _sampleMap["TTJets"]->Hist(target) , "t#bar{t} production", "f");
   legend->AddEntry( _sampleMap["Data"]->Hist(target) , "Data" , "lp" ); 
   legend->Draw();

   printf("Writing to file....");
   canvas->Write();
   delete legend;
   delete stackHist;
   delete canvas;
   printf("Done!\n");
}

//------------------------------------------------------------------------------ 
//   Helper function implementation
//------------------------------------------------------------------------------

void makeTitle( const std::string& target )
{
   title  = availiableList[target].Title();
   xtitle = availiableList[target].Xtitle();
   ytitle = availiableList[target].Ytitle();
   title  = title +";" + xtitle + ";" + ytitle ;
}
