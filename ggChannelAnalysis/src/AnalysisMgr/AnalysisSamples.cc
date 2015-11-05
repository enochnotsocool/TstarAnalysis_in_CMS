/*******************************************************************************
 *
 *  Filename    : AnalysisSamples.cc
 *  Description : Defining samples used in the analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "AnalysisMgr.h"
#include "PlotDef.h"
#include <iostream>

#define LINE_COLOR          kBlack
#define SIGNAL_FILL_COLOR   kWhite
#define TTJETS_FILL_COLOR   kViolet-4 
#define SINGLE_T_FILL_COLOR kCyan-9
#define BOSON_FILL_COLOR    kOrange-4
#define T_PLUS_BOSON_COLOR  kPink-4

//------------------------------------------------------------------------------ 
//   Helper macros functions
//------------------------------------------------------------------------------
#define ADD_SIGNAL_SAMPLE( NAME )                                      \
   _MCsignalMap.insert( SamplePair( #NAME , new SampleMgr( #NAME ) )); \
   _MCsignalMap[ #NAME ]->setFillColor( SIGNAL_FILL_COLOR, 0.0 );      \

#define ADD_BG_SAMPLE( NAME )                                             \
   _MCbackgroundMap.insert( SamplePair( #NAME , new SampleMgr( #NAME ) )); \
   _MCbackgroundMap[ #NAME ]->setLineColor( LINE_COLOR );

void AnalysisMgr::initSamples() 
{
   std::cout << "Adding data sample!" << std::endl;
   //----- Setting update  --------------------------------------------------------
   _dataSample = new SampleMgr( "Data" );
 
   std::cout << "Adding Signals!" << std::endl;
   //----- Setting up signal MC samples  ------------------------------------------
   ADD_SIGNAL_SAMPLE( Tstar_M0700 );
   _MCsignalMap[ "Tstar_M0700" ]->setLineColor( kRed ); 
   ADD_SIGNAL_SAMPLE( Tstar_M0800 );
   _MCsignalMap[ "Tstar_M0800" ]->setLineColor( kCyan  );
   ADD_SIGNAL_SAMPLE( Tstar_M0900 );
   _MCsignalMap[ "Tstar_M0900" ]->setLineColor( kViolet  );
   ADD_SIGNAL_SAMPLE( Tstar_M1000 );
   _MCsignalMap[ "Tstar_M1000" ]->setLineColor( kGreen + 2   );
   ADD_SIGNAL_SAMPLE( Tstar_M1100 );
   _MCsignalMap[ "Tstar_M1100" ]->setLineColor( kBlue );
   ADD_SIGNAL_SAMPLE( Tstar_M1200 );
   _MCsignalMap[ "Tstar_M1200" ]->setLineColor( kOrange-3  );
   ADD_SIGNAL_SAMPLE( Tstar_M1300 );
   _MCsignalMap[ "Tstar_M1300" ]->setLineColor( kAzure-7  );
   ADD_SIGNAL_SAMPLE( Tstar_M1400 );
   _MCsignalMap[ "Tstar_M1400" ]->setLineColor( kOrange+10 );
   ADD_SIGNAL_SAMPLE( Tstar_M1500 );
   _MCsignalMap[ "Tstar_M1500" ]->setLineColor( kCyan+4  );
   ADD_SIGNAL_SAMPLE( Tstar_M1600 );
   _MCsignalMap[ "Tstar_M1500" ]->setLineColor( kRed-3  );


   std::cout << "Adding Backgrounds!" << std::endl;
   //----- Setting up Background samples  -----------------------------------------
   //----- Ordering is for plot convenience  --------------------------------------
   ADD_BG_SAMPLE( 01_TTW_Lepton );
   ADD_BG_SAMPLE( 02_TTW_Quark );
   ADD_BG_SAMPLE( 03_TTZ );
   ADD_BG_SAMPLE( 11_WJets );
   ADD_BG_SAMPLE( 12_ZJets );
   ADD_BG_SAMPLE( 13_WW );
   ADD_BG_SAMPLE( 14_WZ );
   ADD_BG_SAMPLE( 15_ZZ );
   ADD_BG_SAMPLE( 21_SingleT_S );
   ADD_BG_SAMPLE( 22_SingleT_T );
   ADD_BG_SAMPLE( 23_SingleT_TW );
   ADD_BG_SAMPLE( 24_SingleTbar_T );
   ADD_BG_SAMPLE( 25_SingleTbar_TW );
   ADD_BG_SAMPLE( 31_TTJets );

   _MCbackgroundMap["01_TTW_Lepton"]->setFillColor( T_PLUS_BOSON_COLOR );
   _MCbackgroundMap["02_TTW_Quark"]->setFillColor( T_PLUS_BOSON_COLOR );
   _MCbackgroundMap["03_TTZ"]->setFillColor( T_PLUS_BOSON_COLOR );

   _MCbackgroundMap["11_WJets"]->setFillColor( BOSON_FILL_COLOR );
   _MCbackgroundMap["12_ZJets"]->setFillColor( BOSON_FILL_COLOR );
   _MCbackgroundMap["13_WW"]->setFillColor( BOSON_FILL_COLOR );
   _MCbackgroundMap["14_WZ"]->setFillColor( BOSON_FILL_COLOR );
   _MCbackgroundMap["15_ZZ"]->setFillColor( BOSON_FILL_COLOR );

   _MCbackgroundMap["21_SingleT_S"]->setFillColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap["22_SingleT_T"]->setFillColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap["23_SingleT_TW"]->setFillColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap["24_SingleTbar_T"]->setFillColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap["25_SingleTbar_TW"]->setFillColor( SINGLE_T_FILL_COLOR ) ;

   _MCbackgroundMap["31_TTJets"]->setFillColor( TTJETS_FILL_COLOR );

   _combineLegend = new TLegend( 0.75 , 0.75 , 0.95 , 0.95 );
   _combineLegend->AddEntry( _MCsignalMap["Tstar_M1000"]->Hist("JetPt") , "t^{*} signal" , "f" );
   _combineLegend->AddEntry( _MCbackgroundMap["31_TTJets"]->Hist("JetPt") , "t#bar{t} + Jets ", "f");
   _combineLegend->AddEntry( _MCbackgroundMap["21_SingleT_S"]->Hist("JetPt") , "Single top" , "f" );
   _combineLegend->AddEntry( _MCbackgroundMap["11_WJets"]->Hist("JetPt") , "Bosons" , "f" );
   _combineLegend->AddEntry( _MCbackgroundMap["01_TTW_Lepton"]->Hist("JetPt") , "t#bar{t} + Boson" , "f" );
   _combineLegend->AddEntry( _dataSample->Hist("JetPt") , "Data" , "lp" );

   _signalLegend = new TLegend( 0.75 , 0.55 , 0.95 , 0.95 );
   _signalLegend->AddEntry( _MCsignalMap["Tstar_M0700"]->Hist("JetPt") , "M_{t^{*}} 700  GeV/c^{2}" , "l" );
   // _signalLegend->AddEntry( _MCsignalMap["Tstar_M0800"]->Hist("JetPt") , "M_{t^{*}} 800  GeV/c^{2}" , "l" );
   // _signalLegend->AddEntry( _MCsignalMap["Tstar_M0900"]->Hist("JetPt") , "M_{t^{*}} 900  GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap["Tstar_M1000"]->Hist("JetPt") , "M_{t^{*}} 1000 GeV/c^{2}" , "l" );
   // _signalLegend->AddEntry( _MCsignalMap["Tstar_M1100"]->Hist("JetPt") , "M_{t^{*}} 1100 GeV/c^{2}" , "l" );
   // _signalLegend->AddEntry( _MCsignalMap["Tstar_M1200"]->Hist("JetPt") , "M_{t^{*}} 1200 GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap["Tstar_M1300"]->Hist("JetPt") , "M_{t^{*}} 1300 GeV/c^{2}" , "l" );
   // _signalLegend->AddEntry( _MCsignalMap["Tstar_M1400"]->Hist("JetPt") , "M_{t^{*}} 1400 GeV/c^{2}" , "l" );
   // _signalLegend->AddEntry( _MCsignalMap["Tstar_M1500"]->Hist("JetPt") , "M_{t^{*}} 1500 GeV/c^{2}" , "l" );
   _signalLegend->AddEntry( _MCsignalMap["Tstar_M1600"]->Hist("JetPt") , "M_{t^{*}} 1600 GeV/c^{2}" , "l" );

}
