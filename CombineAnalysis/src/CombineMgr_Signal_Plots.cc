/*******************************************************************************
 *
 *  Filename    : SignalPlot.cc
 *  Description : Plotting comparison of signal samples
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"

static TH1F* tempHist;
static float tempScale; 

void CombineMgr::makeSignalPlot( const PlotName& target )
{
   std::string targetName = Stringify( target );
   printf( "making plot %s\n" , targetName.c_str() );
   _stackHist = new THStack( (targetName+"sh").c_str() , (makeHistTitle(target)).c_str() );
   _canvas    = new TCanvas( (targetName+"c").c_str() , targetName.c_str() );
  
   for( auto pair: _MCsignalMap ){
      tempScale= getHistScale( pair.second );
      tempHist = (TH1F*)pair.second->Hist(target)->Clone();
      tempHist->Scale( tempScale );
      tempHist->SetStats(0);
      tempHist->SetFillStyle(0);
      _stackHist->Add( tempHist );
   }
   _stackHist->Draw("nostack");
   _signalLegend->Draw();

   _canvas->Write();
   delete _stackHist;
   delete _canvas;
}
