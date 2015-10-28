/*******************************************************************************
 *
 *  Filename    : PlotStyle.cc
 *  Description : Plot style definitions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "PlotMerging.h"

static const std::string TupleDir = "/wk_cms/yichen/TstarAnalysis/gg_MuonSignal_ntuples/" ;
static const Color_t SingleT_Color = kGreen ;
void PlotMerging::InitSampleStyles() 
{
   _sampleMap["Tstar"]->setTargetEventCount(100.);
   _sampleMap["TTJets"]->setTargetEventCount( 500. );
   _sampleMap["SingleT_Schannel"]->setTargetEventCount( 30. );
   _sampleMap["SingleT_Tchannel_top"]->setTargetEventCount( 30. );
   _sampleMap["SingleT_Tchannel_antitop"]->setTargetEventCount( 30. );
   _sampleMap["SingleT_TWchannel_top"]->setTargetEventCount( 30. );
   _sampleMap["SingleT_TWchannel_antitop"]->setTargetEventCount( 30. );

   _sampleMap["Data"]->addFile( TupleDir+"SingleElectron.root" );
   _sampleMap["Data"]->addFile( TupleDir+"SingleMuon.root" );
   _sampleMap["Data"]->setLineColor( kBlack );

   // Tstar Signal Settings 
   _sampleMap["Tstar"]->addFile( TupleDir+"Tstar_M1000.root" );
   _sampleMap["Tstar"]->setFillColor( kRed );
   _sampleMap["Tstar"]->setLineColor( kBlack );

   // Background settings
   _sampleMap["TTJets"]->addFile( TupleDir+"TTJets.root" );
   _sampleMap["TTJets"]->setFillColor( kOrange + 7 );
   _sampleMap["TTJets"]->setLineColor( kBlack );

   //----- Single To settings  ----------------------------------------------------
   _sampleMap["SingleT_Schannel"]->addFile( TupleDir+"ST_s-channel.root" );
   _sampleMap["SingleT_Schannel"]->setFillColor( SingleT_Color );

   _sampleMap["SingleT_Tchannel_top"]->addFile( TupleDir+"ST_t-channel-top.root" );
   _sampleMap["SingleT_Tchannel_top"]->setFillColor( SingleT_Color );

   _sampleMap["SingleT_Tchannel_antitop"]->addFile( TupleDir+"ST_t-channel_antitop.root" );
   _sampleMap["SingleT_Tchannel_antitop"]->setFillColor( SingleT_Color ); 

   _sampleMap["SingleT_TWchannel_top"]->addFile( TupleDir+"ST_tW_antitop.root" );
   _sampleMap["SingleT_TWchannel_top"]->setFillColor( SingleT_Color ) ;

   _sampleMap["SingleT_TWchannel_antitop"]->addFile( TupleDir+"ST_tW_antitop.root" );
   _sampleMap["SingleT_TWchannel_antitop"]->setFillColor( SingleT_Color );
}
