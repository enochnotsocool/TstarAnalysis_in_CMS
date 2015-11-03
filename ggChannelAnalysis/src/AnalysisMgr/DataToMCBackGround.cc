/*******************************************************************************
 *
 *  Filename    : DataToMCBackGround.cc
 *  Description : Comparing Data to MC background.
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "AnalysisMgr.h"
#include "TLegend.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
   
static TH1F* dataHist;
static TH1F* tempHist;
static float tempScale;

//------------------------------------------------------------------------------ 
//   Public method implementation
//------------------------------------------------------------------------------
void AnalysisMgr::makeDataToBGPlot( const std::string& target )
{
   printf( "making plot %s\n" , target.c_str() );
   _stackHist = new THStack( (target+"sh").c_str() , (makeHistTitle(target)).c_str() );
   _canvas    = new TCanvas( (target+"c").c_str() , target.c_str() );

   //----- Preparing MC  -----------------------------------------------------------
   for( const auto& pair : _MCbackgroundMap ) {
      addMCToStack( pair.second , target ); }
   
   //----- Plotting data  ---------------------------------------------------------
   dataHist = (TH1F*)_dataSample->Hist(target)->Clone();
   float y_max = 1.2* std::max( dataHist->GetMaximum() , _stackHist->GetMaximum() );
   dataHist->SetMaximum( y_max );
   _stackHist->SetMaximum( y_max );
   _stackHist->Draw("hist");
   dataHist->SetStats(0);
   dataHist->Draw("same axis");
   dataHist->Draw("SAME LPE1");

   //----- Legend is previously defined  ------------------------------------------
   _combineLegend->Draw();

   printf("Writing to file....");
   _canvas->Write();
   delete _stackHist;
   delete _canvas;
   printf("Done!\n");
}

//------------------------------------------------------------------------------ 
//   Private helper function implementation
//------------------------------------------------------------------------------
const std::string AnalysisMgr::makeHistTitle( const std::string& target ) const 
{
   std::string xtitle;
   std::string ytitle;
   std::string title;
   
   title  = availiableList[target].Title();
   xtitle = availiableList[target].Xtitle();
   ytitle = availiableList[target].Ytitle();
   title  = title +";" + xtitle + ";" + ytitle ;
   return title;
}

void AnalysisMgr::addMCToStack( SampleMgr* sample, const std::string& target )
{
   tempHist = (TH1F*)( sample->Hist( target )->Clone());
   if( tempHist->Integral() == 0 ){ 
      std::cerr << "Warning Skipping over empty data set: " << sample->name() << std::endl ;
      return ;
   }
   tempScale = getHistScale( sample );
   tempHist->Scale( tempScale ) ; 
   _stackHist->Add( tempHist ); 
   
   printf( "Plotting sample %s, scaling from %f to %f events\n",
         (sample->name()).c_str() ,
         sample->getRawEventCount() ,
         sample->getRawEventCount()*tempScale );
}

float AnalysisMgr::getHistScale( SampleMgr* sample ) const 
{
   float ans = 1.0 ;
   ans  = _totalLumi * sample->crossSection();
   ans *= sample->selectionEff();
   ans /= sample->getRawEventCount();
   return ans;
}

