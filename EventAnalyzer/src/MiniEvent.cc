/***************************************************************************************************
 *
 *  Filename    : MiniEvent.cc
 *  Description : Implementation for MiniEvent Class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : The Key component for this class is the particle and event cleaning algorithms
 *                This algorithms will be implemented directly in the constructor with helper 
 *                functions.
 *
***************************************************************************************************/

#include "TstarAnalysis/EventAnalyzer/interface/MiniEvent.h"

//-------------------------------------------------------------------------------------------------- 
//   Constructor and destructor
//-------------------------------------------------------------------------------------------------- 
MiniEvent::MiniEvent() {};
MiniEvent::~MiniEvent() {};


//-------------------------------------------------------------------------------------------------- 
//   Member access methods
//-------------------------------------------------------------------------------------------------- 
const std::vector<pat::Jet>&      jetList()      const { return _jetList      ; }
const std::vector<pat::Muon>&     muonList()     const { return _muonList     ; }
const std::vector<pat::Electron>& electronList() const { return _electronList ; }
const std::vector<pat::Photon>&   photonList()   const { return _photonList   ; }
const std::vector<pat::MET>&      metList()      const { return _metList      ; }

ULong64_t runNumber()   const { return _runNumber  ; }
ULong64_t eventNumber() const { return _eventNumber; }
ULong64_t lumiNumber()  const { return _lumiNumber ; }

//-------------------------------------------------------------------------------------------------- 
//   Particle cleaning algorithm
//-------------------------------------------------------------------------------------------------- 
#ifdef __EVENTANALYZER_H__ 
MiniEvent::MiniEvent( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   getHandlers( iEvent , iSetup ) ;
   //Begin cleaning algorithm;
   getCleanMuons();
   getCleanElectrons();
   getCleanPhotons();
   getCleanJets();
}

void MiniEvent::getHandlers()
{
   
}

void MiniEvent::getCleanMuons()
{

}

void MiniEvent::getCleanElectrons()
{

}

void MiniEvent::getCleanPhotons()
{

}

void MiniEvent::getCleanJets()
{

}

bool MiniEvent::isCleanMuon( const pat::Muon& ) 
{
   return true;   
}

bool MiniEvent::isCleanElectron( const pat::Electron& ) 
{
   return true;
}

bool MiniEvent::isCleanPhoton( const pat::Photon& )
{
   return true;
}

bool MiniEvent::isCleanJet( const pat::Jet& )
{
   return true;
}

#endif
