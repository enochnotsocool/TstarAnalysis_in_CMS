/***************************************************************************************************
 *
 *  Filename    : EventAnalyzer_cleaner.cc
 *  Description : Functions for particle cleaning algorithm
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
***************************************************************************************************/

#include "TstarAnalysis/EventAnalyzer/interface/EventAnalyzer.h"
void EventAnalyzer::getHandlers( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   iEvent.getByLabel( "slimmedJets"      , _rawJetList      ) ;
   iEvent.getByLabel( "slimmedMuons"     , _rawMuonList     ) ;
   iEvent.getByLabel( "slimmedElectrons" , _rawElectronList ) ;
   iEvent.getByLabel( "slimmedPhotons"   , _rawPhotonList   ) ;
}

void EventAnalyzer::getCleanMuons()
{
   for( const auto& muon : _rawMuonList ) {
      if( isCleanMuon( *muon ) ) {
         _muonList.push_back( *muon ) ;
      } 
   }
}

void EventAnalyzer::getCleanElectrons()
{

}

void EventAnalyzer::getCleanPhotons()
{

}

void EventAnalyzer::getCleanJets()
{

}

bool EventAnalyzer::isCleanMuon( const pat::Muon& ) const  
{
   return true;   
}

bool EventAnalyzer::isCleanElectron( const pat::Electron& )  const
{
   return true;
}

bool EventAnalyzer::isCleanPhoton( const pat::Photon& ) const
{
   return true;
}

bool EventAnalyzer::isCleanJet( const pat::Jet& ) const
{
   return true;
}

