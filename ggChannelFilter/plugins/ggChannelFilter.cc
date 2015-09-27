/*******************************************************************************
 *
 *  Filename    : ggChannelFilter.cc
 *  Description : ED Plugini setups for ggChannel Event Selection
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/ggChannelFilter/interface/ggChannelFilter.h"
#include <iostream>
ggChannelFilter::ggChannelFilter( const edm::ParameterSet& iConfig )
{
   _muonsrc = iConfig.getParameter<edm::InputTag>( "muonsrc" );
   _elecsrc = iConfig.getParameter<edm::InputTag>( "elecsrc" );
   _jetsrc  = iConfig.getParameter<edm::InputTag>( "jetsrc"  );
   _vertexsrc = iConfig.getParameter<edm::InputTag>( "vertexsrc" ); 
}


ggChannelFilter::~ggChannelFilter()
{ }


// ------------ method called on each new Event  ------------
bool
ggChannelFilter::filter( edm::Event& iEvent, const edm::EventSetup& iSetup )
{
   _looseJetList.clear();
   _looseElecList.clear();
   _looseMuonList.clear();
   _tightElecList.clear();
   _tightMuonList.clear();

   totalEvent++;
   if( !getPrimaryVertex(iEvent, iSetup) ) { return false; }
   if( !passMuonCleaning(iEvent, iSetup) ) { return false; }
   if( !passElectronCleaning(iEvent, iSetup) ) { return false; }
   if( !passJetCleaning(iEvent, iSetup) ) { return false; }
   if( !passEventSelection(iEvent, iSetup) ) { return false; }

   passedEvent++;
   return true;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void ggChannelFilter::beginStream( edm::StreamID )
{
   totalEvent = 0 ;
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
ggChannelFilter::endStream()
{
   std::cout << "Total Events:" << totalEvent << std::endl;
   std::cout << "Passed Events:" << passedEvent << std::endl ; 
}

void
ggChannelFilter::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
   //The following says we do not know what parameters are allowed so do no validation
   // Please change this to state exactly what you do use, even if it is no parameters
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault( desc );
}
//define this as a plug-in
DEFINE_FWK_MODULE( ggChannelFilter );
