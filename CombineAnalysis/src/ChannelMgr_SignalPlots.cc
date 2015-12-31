/*******************************************************************************
 *
 *  Filename    : SignalPlot.cc
 *  Description : Plotting comparison of signal samples
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include "THStack.h"
#include "TCanvas.h"
#include <algorithm>

using namespace std;

void ChannelMgr::MakeSignalPlot( const PlotName& target )
{
   std::string targetName = Stringify( target );
   TH1F* tempHist;
   float tempScale; 

   printf( "making plot %s\n" , targetName.c_str() );
   //----- Declaring drawing objects  ---------------------------------------------
   TFile* plotFile = openPlotFile();
   TCanvas* canvas = new TCanvas( (targetName+"canvas").c_str() , targetName.c_str() );
   THStack* stack  = new THStack( (targetName+"stack").c_str() , (makeHistTitle(target)).c_str() );
   TLegend* sl     = new TLegend( 0.75 , 0.55 , 0.95 , 0.95 );
   makeSignalLegend(sl,target);

   for( const auto& pair: _MCsignalMap ){
      tempScale= getHistScale( pair.second );
      tempHist = (TH1F*)pair.second->Hist(target)->Clone();
      tempHist->Scale( tempScale );
      tempHist->SetFillStyle(0);
      stack->Add( tempHist );
   }
   setFontStyle(dynamic_cast<TH1F*>(stack));
   setXAxisFont(dynamic_cast<TH1F*>(stack));

   stack->Draw("nostack");
   sl->Draw();

   canvas->Write();
   delete stack;
   delete canvas;
   delete sl;
   plotFile->Close();
   delete plotFile;
}

void ChannelMgr::MakeInSampleComparison
( const SampleName& sample , const PlotName& plot1 , const PlotName& plot2 )
{
   string plotName = Stringify( plot1 ) + "_vs_" + Stringify( plot2 );
   string sName = Stringify(sample);
   printf( "Making plot of %s in sample %s\n" , plotName.c_str() , sName.c_str() );
   
   TFile* plotFile = openPlotFile();
   TH1F* hist1     = (TH1F*)_MCsignalMap[sample]->Hist( plot1 )->Clone();
   TH1F* hist2     = (TH1F*)_MCsignalMap[sample]->Hist( plot2 )->Clone(); 
   TCanvas* canvas = new TCanvas( (sName+plotName).c_str() , (sName+plotName).c_str() );
   TLegend* comp   = new TLegend( 0.65, 0.75 , 0.95 , 0.95 );
   
   hist1->SetLineColor( kBlue+2 );
   hist2->SetLineColor( kRed+2 );
   matchHeights( hist1, hist2 );
   setFontStyle( hist1 );
   setXAxisFont( hist1 );
   hist1->SetTitle( makeHistTitle(plot1).c_str() );

   hist1->Draw("A");
   hist1->Draw("HIST");
   hist2->Draw("HIST SAME");
   
   comp->AddEntry( hist1 , Stringify(plot1).c_str() , "l" ); 
   comp->AddEntry( hist2 , Stringify(plot2).c_str() , "l" ); 
   comp->Draw();

   canvas->Write();
   delete canvas;
   delete comp;
   plotFile->Close();
   delete plotFile;
}

//------------------------------------------------------------------------------ 
//   Helper Private Members
//------------------------------------------------------------------------------
void ChannelMgr::makeSignalLegend( TLegend* x , const PlotName& target )
{
   x->AddEntry( _MCsignalMap[Tstar_M0700]->Hist(target) , "M_{t^{*}} 700  GeV/c^{2}" , "l" );
   x->AddEntry( _MCsignalMap[Tstar_M0800]->Hist(target) , "M_{t^{*}} 800  GeV/c^{2}" , "l" );
   x->AddEntry( _MCsignalMap[Tstar_M0900]->Hist(target) , "M_{t^{*}} 900  GeV/c^{2}" , "l" );
   x->AddEntry( _MCsignalMap[Tstar_M1000]->Hist(target) , "M_{t^{*}} 1000 GeV/c^{2}" , "l" );
   x->AddEntry( _MCsignalMap[Tstar_M1100]->Hist(target) , "M_{t^{*}} 1100 GeV/c^{2}" , "l" );
   x->AddEntry( _MCsignalMap[Tstar_M1200]->Hist(target) , "M_{t^{*}} 1200 GeV/c^{2}" , "l" );
   x->AddEntry( _MCsignalMap[Tstar_M1300]->Hist(target) , "M_{t^{*}} 1300 GeV/c^{2}" , "l" );
   x->AddEntry( _MCsignalMap[Tstar_M1400]->Hist(target) , "M_{t^{*}} 1400 GeV/c^{2}" , "l" );
   x->AddEntry( _MCsignalMap[Tstar_M1500]->Hist(target) , "M_{t^{*}} 1500 GeV/c^{2}" , "l" );
   x->AddEntry( _MCsignalMap[Tstar_M1600]->Hist(target) , "M_{t^{*}} 1600 GeV/c^{2}" , "l" );
}
