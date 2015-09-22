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
void EventAnalyzer::getHandlers( const edm::Event& , const edm::EventSetup& )
{
   
}

void EventAnalyzer::getCleanMuons()
{

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

