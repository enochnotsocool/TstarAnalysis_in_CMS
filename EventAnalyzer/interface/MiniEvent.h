/***************************************************************************************************
 *
 *  Filename    : MiniEvent.h
 *  Description : Using a custom Event Class for ease of acces
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : Here, we will only be storing the objects of interest in a std::vector
 *
***************************************************************************************************/
#ifndef __MINIEVENT_H__
#define __MINIEVENT_H__

#include <vector>
//-------------------------------------------------------------------------------------------------- 
//   CMSSW Libraries
//-------------------------------------------------------------------------------------------------- 
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"

class MiniEvent {
public:
   MiniEvent ();
   virtual ~MiniEvent ();
   // Data Member access functions
   const std::vector<pat::Jet>&      jetList()      const ;
   const std::vector<pat::Muon>&     muonList()     const ;
   const std::vector<pat::Electron>& electronList() const ;
   const std::vector<pat::Photon>&   photonList()   const ;
   const std::vector<pat::MET>&      metList()      const ;

   ULong64_t runNumber()   const ;
   ULong64_t eventNumber() const ;
   ULong64_t lumiNumber()  const ; 

   // Event Selection specific methods
#ifdef __EVENTANALYZER_H__
   MiniEvent ( const edm:Event& , const edm::EvetSetup& ):
#endif

private:
   // Physical object list
   std::vector<pat::Jet>      _jetList;
   std::vector<pat::Muon>     _muonList;
   std::vector<pat::Electron> _electronList;
   std::vector<pat::Photon>   _photonList;
   std::vector<pat::MET>      _metList;

   // Event specific objects list
   ULong64_t    _runNumber;
   ULong64_t    _eventNumber;
   ULong64_t    _lumiNumber;

#ifdef __EVENTANALYZER_H__
   // Raw interaction data members
   edm::Handle<edm::View<pat::Jet>>      _rawJetList;
   edm::Handle<edm::View<pat::Muon>>     _rawMuonList;
   edm::Handle<edm::View<pat::Electron>> _rawElectronList;
   edm::Handle<edm::View<pat::Photon>>   _rawPhotonList;
   edm::Handle<edm::View<pat::MET>>      _rawMETList;

   void getHandlers( const edm::Event& , const edm::EvetnSetup );
   // Cleaning algorithm helper functions
   void getCleanMuons();
   void getCleanElectrons();
   void getCleanPhotons() ;
   void getCleanJets();

   bool isCleanMuon( const pat::Muon& ) const ;
   bool isCleanElectron( const pat::Electron& );
   bool isCleanPhoton( const pat::Photon& ) ;
   bool isCleanJet( const pat::Jet& );
#endif
};

#endif // __MINIEVENT_H__

