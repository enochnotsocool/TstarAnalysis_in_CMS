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
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"

//-------------------------------------------------------------------------------------------------- 
//   Helper ROOT Libraries
//-------------------------------------------------------------------------------------------------- 
#include "TH1F.h"

//------------------------------------------------------------------------------ 
//   Self written helper classes
//------------------------------------------------------------------------------
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
   double rho ; // Specially declared since it is used for many particle selections
   reco::Vertex               _primaryVertex  ;
   std::vector<reco::Vertex>  _vertexList  ;
   std::vector<pat::Jet>      _jetList     ;
   std::vector<pat::Muon>     _muonList    ;
   std::vector<pat::Electron> _electronList;
   std::vector<pat::Photon>   _photonList  ;
   
   void getCleanParticles( const edm::Event& , const edm::EventSetup& );
   // Cleaning algorithm helper functions
   bool isGoodPV( const reco::Vertex& ) const ;
   bool isCleanMuon( const pat::Muon& ) const ;
   bool isCleanElectron( const pat::Electron& ) const ;
   bool isCleanPhoton( const pat::Photon& ) const ;
   bool isCleanJet( const pat::Jet& ) const ;

   double el_CRpfIso( const pat::Electron& ) const ;
   double el_EffArea( const pat::Electron& ) const ;
   double mu_CRpfIso( const pat::Muon& ) const ;

   //-------------------------------------------------------------------------------------------------- 
   //   Preliminary Graphs
   //--------------------------------------------------------------------------------------------------
   TH1F* jetSelection;
};

#endif // __EVENTANALYZER_H__



