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

#include <iostream>
#include <algorithm>
#include "TrackingTools/IPTools/interface/IPTools.h"

//-------------------------------------------------------------------------------------------------- 
//   Helper functions and Macros
//--------------------------------------------------------------------------------------------------
#define MAKELIST( TYPE , NAME  , LABEL )                          \
   edm::Handle<edm::View<TYPE::NAME>>  NAME ## Handle;      \
   iEvent.getByLabel( LABEL , NAME ## Handle ) ;           \
   const edm::View<TYPE::NAME>&  raw ## NAME ## List =  *(NAME ## Handle.product());

double DeltaBeta_04( const pat::Muon& );

//-------------------------------------------------------------------------------------------------- 
//   Member function implementations
//-------------------------------------------------------------------------------------------------- 
void EventAnalyzer::getPrimaryVertex( const edm::Event& iEvent , const edm::EventSetup& iSetup ) 
{
   MAKELIST( reco ,  Vertex , "offlineSlimmedPrimaryVertices" ) ;
   for( const auto& vertex : rawVertexList ) {
      if( isGoodPV( vertex ) ) {
         _primaryVertex = vertex ;
         break;
      } 
   }   
}


void EventAnalyzer::getCleanParticles( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{

   MAKELIST( pat , Muon     , "slimmedMuons"     );
   MAKELIST( pat , Electron , "slimmedElectrons" );
   MAKELIST( pat , Photon   , "slimmedPhotons"   );
   MAKELIST( pat , Jet      , "slimmedJets"      );

   _muonList.clear() ;
   _electronList.clear();
   _jetList.clear();
   _photonList.clear();
   //-------------------------------------------------------------------------------------------------- 
   //   Particle Flow cleaning
   //      Muon -> electron -> photon -> Jet
   //-------------------------------------------------------------------------------------------------- 
   for( const auto& muon : rawMuonList ) {
      if( isCleanMuon( muon ) ){
         _muonList.push_back( muon ) ; }
   }
   for( const auto& elec : rawElectronList ) {
      if( isCleanElectron( elec ) ) {
         _electronList.push_back( elec ) ; }
   }
   for( const auto& pho : rawPhotonList ) {
      if( isCleanPhoton( pho ) ) {
         _photonList.push_back(pho) ; }
   }
   for( const auto& jet : rawJetList ) {
      if( isCleanJet( jet ) ) {
         _jetList.push_back( jet ) ; }
   }
   std::cout << "Muons: "   << _muonList.size()-rawMuonList.size() << " "
      << "electrons: " << _electronList.size()-rawElectronList.size() << " "
      << "Photons: " << _photonList.size()-rawPhotonList.size() << " "
      << "jets: " << _jetList.size()-rawJetList.size() << std::endl;
}

bool EventAnalyzer::isGoodPV( const reco::Vertex& v ) const 
{
   if( v.isFake() ) { return false; }
   if( v.ndof() < 4 ) { return false; } 
   if( v.z()    >=24 ) { return false; }
   if( v.position().Rho() >=2 ) { return false;}
   return true;
}

bool EventAnalyzer::isCleanMuon( const pat::Muon& mu ) const  
{
   // Standard selection for tight muon:
   // https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Tight_Muon
   if( ! muon::isTightMuon( mu, _primaryVertex ) ) { return false;}
   if( DeltaBeta_04( mu ) > 0.12 ) { return false ; }
   if( mu.pt()         < 20 ) { return false ; }
   if( abs( mu.eta() ) > 2.1) { return false ; }
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
//-------------------------------------------------------------------------------------------------- 
//   Helper function implementation
//--------------------------------------------------------------------------------------------------

double DeltaBeta_04( const pat::Muon& mu )
{
   double ans ;
   double chgIso = mu.pfIsolationR04().sumChargedHadronPt ;
   double neuIso = mu.pfIsolationR04().sumNeutralHadronEt ;
   double phoIso = mu.pfIsolationR04().sumPhotonEt;
   double sumPU  = mu.pfIsolationR04().sumPUPt;

   ans  = chgIso + std::max( 0. , neuIso + phoIso - 0.5*sumPU ) ;
   ans /= mu.pt();
   return ans;
}
