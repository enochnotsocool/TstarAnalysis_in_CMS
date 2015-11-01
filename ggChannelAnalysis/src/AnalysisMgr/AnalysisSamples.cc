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
#define SIGNAL_FILL_COLOR   kRed
#define TTJETS_FILL_COLOR   kOrange+7 
#define SINGLE_T_FILL_COLOR kCyan 
#define WJETS_FILL_COLOR    kGreen

//------------------------------------------------------------------------------ 
//   Helper macros functions
//------------------------------------------------------------------------------
#define ADD_SIGNAL_SAMPLE( NAME )                                      \
   _MCsignalMap.insert( SamplePair( #NAME , new SampleMgr( #NAME ) )); \
   _MCsignalMap[ #NAME ]->setFillColor( SIGNAL_FILL_COLOR );           \
   _MCsignalMap[ #NAME ]->setLineColor( LINE_COLOR );

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
   ADD_SIGNAL_SAMPLE( Tstar_M0800 );
   ADD_SIGNAL_SAMPLE( Tstar_M0900 );
   ADD_SIGNAL_SAMPLE( Tstar_M1000 );
   ADD_SIGNAL_SAMPLE( Tstar_M1100 );
   ADD_SIGNAL_SAMPLE( Tstar_M1200 );
   ADD_SIGNAL_SAMPLE( Tstar_M1300 );
   ADD_SIGNAL_SAMPLE( Tstar_M1400 );
   ADD_SIGNAL_SAMPLE( Tstar_M1500 );
   ADD_SIGNAL_SAMPLE( Tstar_M1600 );


   std::cout << "Adding Backgrounds!" << std::endl;
   //----- Setting up Background samples  -----------------------------------------
   //----- Ordering is for plot convenience  --------------------------------------
   ADD_BG_SAMPLE( 01_SingleT_S );
   ADD_BG_SAMPLE( 02_SingleT_T );
   ADD_BG_SAMPLE( 03_SingleT_TW );
   ADD_BG_SAMPLE( 04_SingleTbar_T );
   ADD_BG_SAMPLE( 05_SingleTbar_TW );
   ADD_BG_SAMPLE( 06_WJets );
   ADD_BG_SAMPLE( 07_TTJets );
   _MCbackgroundMap["01_SingleT_S"]->setFillColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap["02_SingleT_T"]->setFillColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap["03_SingleT_TW"]->setFillColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap["04_SingleTbar_T"]->setFillColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap["05_SingleTbar_TW"]->setFillColor( SINGLE_T_FILL_COLOR ) ;
   _MCbackgroundMap["06_WJets"]->setFillColor( WJETS_FILL_COLOR );
   _MCbackgroundMap["07_TTJets"]->setFillColor( TTJETS_FILL_COLOR );

   _combineLegend = new TLegend( 0.75 , 0.75 , 0.95 , 0.95 );
   _combineLegend->AddEntry( _MCsignalMap["Tstar_M1000"]->Hist("JetPt") , "t^{*} signal" , "f" );
   _combineLegend->AddEntry( _MCbackgroundMap["01_SingleT_S"]->Hist("JetPt") , "Single top" , "f" );
   _combineLegend->AddEntry( _MCbackgroundMap["07_TTJets"]->Hist("JetPt") , "TT + Jets ", "f");
   _combineLegend->AddEntry( _dataSample->Hist("JetPt") , "Data" , "lp" ); 
}
