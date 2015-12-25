/*******************************************************************************
 *
 *  Filename    : SignalPlot.cc
 *  Description : Plotting comparison of signal samples
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include <algorithm>

using namespace std;

void CombineMgr::MakeSignalPlot( const PlotName& target )
{
   TH1F* tempHist;
   float tempScale; 

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

void CombineMgr::MakeInSampleComparison
( const SampleName& sample , const PlotName& plot1 , const PlotName& plot2 )
{
   string plotName = Stringify( plot1 ) + "_vs_" + Stringify( plot2 ); 
   TH1F* hist1 = (TH1F*)_MCsignalMap[sample]->Hist( plot1 )->Clone();
   TH1F* hist2 = (TH1F*)_MCsignalMap[sample]->Hist( plot2 )->Clone(); 
   float yrange = 0 ; 
   _canvas = new TCanvas( (Stringify(sample)+plotName).c_str() , (Stringify(sample)+plotName).c_str() );
   
   printf( "Making plot of %s in sample %s\n" , 
         plotName.c_str() , Stringify( sample ).c_str() );

   hist1->SetLineColor( kBlue+2 );
   hist2->SetLineColor( kRed+2 );
   yrange = 1.3 * max( hist1->GetMaximum() , hist2->GetMaximum() );
   hist1->SetMaximum( yrange );
   hist1->SetFillStyle(0);
   hist1->SetStats(0);
   hist2->SetMaximum( yrange );
   hist2->SetFillStyle(0);
   hist2->SetStats(0);

   hist1->Draw("A");
   hist1->Draw("HIST");
   hist2->Draw("HIST SAME");
   
   TLegend* comp = new TLegend( 0.65, 0.65 , 0.95 , 0.95 );
   comp->AddEntry( hist1 , Stringify(plot1).c_str() , "l" ); 
   comp->AddEntry( hist2 , Stringify(plot2).c_str() , "l" ); 
   comp->Draw();

   _canvas->Write();
   delete _canvas;
}
