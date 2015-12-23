/*******************************************************************************
 *
 *  Filename    : AnalysisSamples.cc
 *  Description : Defining samples used in the analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/PlotDef.h"
#include <iostream>

#define LINE_COLOR          kBlack
#define SIGNAL_FILL_COLOR   kWhite
#define TTJETS_FILL_COLOR   (kBlue-6)
#define SINGLE_T_FILL_COLOR (kCyan-2)
#define BOSON_FILL_COLOR    (kOrange+7)
#define T_PLUS_BOSON_COLOR  (kPink-4)

//------------------------------------------------------------------------------ 
//   Helper macros functions
//------------------------------------------------------------------------------
#define ADD_SIGNAL_SAMPLE( NAME )                                      \
   _MCsignalMap.insert( SamplePair( NAME , new SampleMgr( NAME ) )); \
   _MCsignalMap[ NAME ]->setFillColor( SIGNAL_FILL_COLOR, 0.0 );      \

#define ADD_BG_SAMPLE( NAME )                                             \
   _MCbackgroundMap.insert( SamplePair( NAME , new SampleMgr( NAME ) )); \

void CombineMgr::initSamples() 
{
   std::cout << "Adding data sample!" << std::endl;
   //----- Setting update  --------------------------------------------------------
   _dataSample = new SampleMgr( Data );
 
   std::cout << "Adding Signals!" << std::endl;
   //----- Setting up signal MC samples  ------------------------------------------
   ADD_SIGNAL_SAMPLE( Tstar_M0700 );
   _MCsignalMap[ Tstar_M0700 ]->setLineColor( kRed ); 
   ADD_SIGNAL_SAMPLE( Tstar_M0800 );
   _MCsignalMap[ Tstar_M0800 ]->setLineColor( kCyan  );
   ADD_SIGNAL_SAMPLE( Tstar_M0900 );
   _MCsignalMap[ Tstar_M0900 ]->setLineColor( kViolet  );
   ADD_SIGNAL_SAMPLE( Tstar_M1000 );
   _MCsignalMap[ Tstar_M1000 ]->setLineColor( kGreen + 2   );
   ADD_SIGNAL_SAMPLE( Tstar_M1100 );
   _MCsignalMap[ Tstar_M1100 ]->setLineColor( kBlue );
   ADD_SIGNAL_SAMPLE( Tstar_M1200 );
   _MCsignalMap[ Tstar_M1200 ]->setLineColor( kOrange-3  );
   ADD_SIGNAL_SAMPLE( Tstar_M1300 );
   _MCsignalMap[ Tstar_M1300 ]->setLineColor( kAzure-7  );
   ADD_SIGNAL_SAMPLE( Tstar_M1400 );
   _MCsignalMap[ Tstar_M1400 ]->setLineColor( kOrange+10 );
   ADD_SIGNAL_SAMPLE( Tstar_M1500 );
   _MCsignalMap[ Tstar_M1500 ]->setLineColor( kCyan+4  );
   ADD_SIGNAL_SAMPLE( Tstar_M1600 );
   _MCsignalMap[ Tstar_M1500 ]->setLineColor( kRed-3  );


   std::cout << "Adding Backgrounds!" << std::endl;
   //----- Setting up Background samples  -----------------------------------------
   ADD_BG_SAMPLE( TTW_Lepton );
   ADD_BG_SAMPLE( TTW_Quark );
   ADD_BG_SAMPLE( TTZ_Lepton );
   ADD_BG_SAMPLE( TTZ_Quark );
   ADD_BG_SAMPLE( WJets );
   ADD_BG_SAMPLE( ZJets );
   ADD_BG_SAMPLE( WW );
   ADD_BG_SAMPLE( WZ );
   ADD_BG_SAMPLE( ZZ );
   ADD_BG_SAMPLE( SingleT_S );
   ADD_BG_SAMPLE( SingleT_T );
   ADD_BG_SAMPLE( SingleT_TW );
   ADD_BG_SAMPLE( SingleTbar_TW );
   ADD_BG_SAMPLE( TTJets );

   _MCbackgroundMap[TTW_Lepton]->setColor( T_PLUS_BOSON_COLOR );
   _MCbackgroundMap[TTW_Quark]->setColor( T_PLUS_BOSON_COLOR );
   _MCbackgroundMap[TTZ_Lepton]->setColor( T_PLUS_BOSON_COLOR );
   _MCbackgroundMap[TTZ_Quark]->setColor( T_PLUS_BOSON_COLOR );
   _MCbackgroundMap[TTZ_Quark]->setLineColor( LINE_COLOR );

   _MCbackgroundMap[WJets]->setColor( BOSON_FILL_COLOR );
   _MCbackgroundMap[ZJets]->setColor( BOSON_FILL_COLOR );
   _MCbackgroundMap[WW]->setColor( BOSON_FILL_COLOR );
   _MCbackgroundMap[WZ]->setColor( BOSON_FILL_COLOR );
   _MCbackgroundMap[ZZ]->setColor( BOSON_FILL_COLOR );
   _MCbackgroundMap[ZZ]->setLineColor( LINE_COLOR );

   _MCbackgroundMap[SingleT_S]->setColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap[SingleT_T]->setColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap[SingleT_TW]->setColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap[SingleTbar_TW]->setColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap[SingleTbar_TW]->setLineColor( LINE_COLOR ) ;

   _MCbackgroundMap[TTJets]->setColor( TTJETS_FILL_COLOR );
   _MCbackgroundMap[TTJets]->setLineColor( LINE_COLOR );


   _signalLegend = new TLegend( 0.75 , 0.55 , 0.95 , 0.95 );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M0700]->Hist(JetPt) , "M_{t^{*}} 700  GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M0800]->Hist(JetPt) , "M_{t^{*}} 800  GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M0900]->Hist(JetPt) , "M_{t^{*}} 900  GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M1000]->Hist(JetPt) , "M_{t^{*}} 1000 GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M1100]->Hist(JetPt) , "M_{t^{*}} 1100 GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M1200]->Hist(JetPt) , "M_{t^{*}} 1200 GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M1300]->Hist(JetPt) , "M_{t^{*}} 1300 GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M1400]->Hist(JetPt) , "M_{t^{*}} 1400 GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M1500]->Hist(JetPt) , "M_{t^{*}} 1500 GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap[Tstar_M1600]->Hist(JetPt) , "M_{t^{*}} 1600 GeV/c^{2}" , "l" );

}
