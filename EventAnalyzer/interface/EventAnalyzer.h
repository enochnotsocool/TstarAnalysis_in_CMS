/*******************************************************************************
 *
 *  Filename    : EventAnalyzer.h
 *  Description : The interaction framework with the CMSSW framework
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : All events are stored in the _masterList, 
 *                Events will only include cleaned particles. 
 *
*******************************************************************************/
#ifndef __EVENTANALYZER_H__
#define __EVENTANALYZER_H__

//------------------------------------------------------------------------------ 
//   EDAnalyzer requirements
//------------------------------------------------------------------------------
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//------------------------------------------------------------------------------ 
//   Self written helper classes
//------------------------------------------------------------------------------
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "TstarAnalysis/EventAnalyzer/interface/MiniEvent.h"
#include "TstarAnalysis/EventAnalyzer/interface/Region.h"

class EventAnalyzer : public edm::EDAnalyzer  {
public:
   explicit EventAnalyzer( const edm::ParameterSet& );
   ~EventAnalyzer();
   static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );

private:
   virtual void beginJob() override;
   virtual void analyze( const edm::Event&, const edm::EventSetup& ) override;
   virtual void endJob() override;
   
   std::vector<Region*>   _regionList;

   void makeEvent( MiniEvent* , const edm::Event& , const edm::EventSetup& ) const ;
   //----- Private data members  -----------------------------------------------
   reco::Vertex    _primaryVertex  ;
   std::vector<pat::Jet>      _jetList     ;
   std::vector<pat::Muon>     _muonList    ;
   std::vector<pat::Electron> _electronList;
   std::vector<pat::Photon>   _photonList  ;
   
   
   // Raw interaction data members
   edm::Handle<edm::View<pat::Jet>>      _rawJetList;
   edm::Handle<edm::View<pat::Muon>>     _rawMuonList;
   edm::Handle<edm::View<pat::Electron>> _rawElectronList;
   edm::Handle<edm::View<pat::Photon>>   _rawPhotonList;

   void getPrimaryVertex( const edm::Event& , const edm::EventSetup& ) ;
   void getCleanParticles( const edm::Event& , const edm::EventSetup& );
   // Cleaning algorithm helper functions
   bool isGoodPV( const reco::Vertex& ) const ;
   bool isCleanMuon( const pat::Muon& ) const ;
   bool isCleanElectron( const pat::Electron& ) const ;
   bool isCleanPhoton( const pat::Photon& ) const ;
   bool isCleanJet( const pat::Jet& ) const ;
};

#endif // __EVENTANALYZER_H__



