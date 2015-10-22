/*******************************************************************************
 *
 *  Filename    : SampleDef.cc
 *  Description : Declaration of Sample objects and initialization
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include <string>
#include "SampleDef.h"

SampleInfo Data( "Data" );
SampleInfo Tstar_Signal( "Tstar" );
SampleInfo TTJets_background( "TTJets" ); 
SampleInfo SingleT_s_channel( "SingleT_s_channel" );
SampleInfo SingleT_t_channel_top( "SingleT_t_channel_top" );
SampleInfo SingleT_t_channel_antitop("SingleT_t_channel_antitop");
SampleInfo SingleT_tW_channel_top("SingleT_tW_channel_top");
SampleInfo SingleT_tW_channel_antitop("SingleT_tW_channel_antitop");

static const std::string TupleDir = "/wk_cms/yichen/TstarAnalysis/ggChannel_stripped_ntuples/" ;
void InitSamples()
{
   // Data File Settings 
   Data.addFile( TupleDir+"SingleElectron.root" );
   Data.addFile( TupleDir+"SingleMuon.root" );

   // Tstar Signal Settings 
   Tstar_Signal.addFile( TupleDir+"Tstar_M1000.root" );

   // Background settings
   TTJets_background.addFile( TupleDir+"TTJets.root" );

   SingleT_s_channel.addFile( TupleDir+"ST_s-channel.root" );
   SingleT_t_channel_top.addFile( TupleDir+"ST_t-channel-top.root" );
   SingleT_t_channel_antitop.addFile( TupleDir+"ST_t-channel_antitop.root" );
   SingleT_tW_channel_top.addFile( TupleDir+"ST_tW_antitop.root" );
   SingleT_tW_channel_antitop.addFile( TupleDir+"ST_tW_antitop.root" );
}
