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
#include "TLorentzVector.h"

#include "TrackingTools/IPTools/interface/IPTools.h"

//-------------------------------------------------------------------------------------------------- 
//   Helper functions and Macros
//--------------------------------------------------------------------------------------------------
#define MAKELIST( TYPE , NAME  , LABEL )                          \
   edm::Handle<edm::View<TYPE::NAME>>  NAME ## Handle;      \
   iEvent.getByLabel( LABEL , NAME ## Handle ) ;           \
   const edm::View<TYPE::NAME>&  raw ## NAME ## List =  *(NAME ## Handle.product());

//-------------------------------------------------------------------------------------------------- 
//   Member function implementations
//-------------------------------------------------------------------------------------------------- 
void EventAnalyzer::getCleanParticles( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{

   MAKELIST( reco , Vertex   , "offlineSlimmedPrimaryVertices" ) ;
   MAKELIST( pat  , Muon     , "slimmedMuons"                  ) ;
   MAKELIST( pat  , Electron , "slimmedElectrons"              ) ;
   MAKELIST( pat  , Jet      , "slimmedJets"                   ) ;
   
   _vertexList.clear();
   _muonList.clear() ;
   _electronList.clear();
   _jetList.clear();
   bool hasPV = false;
   //-------------------------------------------------------------------------------------------------- 
   //   Particle Flow cleaning
   //      Vertex -> Muon -> electron -> photon -> Jet
   //-------------------------------------------------------------------------------------------------- 
   for( const auto& vertex : rawVertexList ) {
      if( !hasPV && isGoodPV( vertex ) ) {
         _primaryVertex = vertex ;
         hasPV = true;
      } 
   }   
   for( const auto& muon : rawMuonList ) {
      if( isTightMuon( muon ) ){
         _tightMuonList.push_back( &muon ) ;
      } else if ( isLooseMuon( muon ) ){
         _looseMuonList.push_back( &muon ) ; 
      }
   }
   for( const auto& elec : rawElectronList ) {
      if( isTightElec( elec ) ) {
         _tightElecList.push_back( elec ) ; 
      } else if( isLooseMuon( elec ) ){
         _looseElecList.push_back( elec ) ;
      }
   }
   for( const auto& jet : rawJetList ) {
      if( isLooseJet( jet ) ) {
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
//----- Muon Selection  ----------------------------------------------------------------------------
bool EventAnalyzer::isLooseMuon( const pat::Muon& mu ) const 
{
   if( !muon::isLooseMuon( mu , _primaryVertex ) ){ return false; } 
   if( mu.pt() < 10 ) { return false; }
   if( abs( mu.eta() ) < 2.5 ) { return false; } 
   if( mu_CRpfIso( mu ) > 0.2 ) { return false; }
   return true;
}

bool EventAnalyzer::isTightMuon( const pat::Muon& mu ) const  
{
   if( !muon::isTightMuon( mu, _primaryVertex ) ) { return false;}
   if( mu.pt()         < 20 ) { return false ; }
   if( abs( mu.eta() ) > 2.1) { return false ; }
   if( mu_CRpfIso( mu ) > 0.12 ) { return false ; }
   return true;
}


//----- Electron selection  ------------------------------------------------------------------------
bool EventAnalyzer::sTightElec( const pat::Electron& el ) const 
{
   if( el.pt() < 20 ) { return false; }
   if( abs(el.eta()) > 2.5) { return false; } 
   // if(  MVA < 0.0 ) { return false; }
   if( el_CRpfIso( el ) > 1.5 ) { return false; } 
   return true;   
}

bool EventAnalyzer::isTightElec( const pat::Electron& el )  const
{
   if( el.pt() < 30 ) { return false; }
   if( abs(el.eta()) > 1.5 ) { return false; } 
   if( abs(el.eta()) > 1.4442 && abs(el.eta()) < 1.566 ) { return false; }
   if( el.gsfTrack()->dxy( _primaryVertex.position() ) >= 0.2 ) { return false; }
   // if( MVA < 0.5 ) { return false; }
   // conversion photon
   if( el_CRpfIso( el ) >= 0.1 ) { return false; }
   return true;
}

//----- Jet Selection  -----------------------------------------------------------------------------
bool EventAnalyzer::isLooseJet( const pat::Jet& jet ) const
{
   std::cout << "Enter clean jet Sub routine" << std::endl;
   jetSelection->Fill(0.);
   if( jet.pt() < 30.0 ) { return false; }
   jetSelection->Fill(1.);
   if( abs( jet.eta() ) > 2.5 ) { return false; }

   jetSelection->Fill(2.);
   // Loose JetID 
   if( jet.neutralHadronEnergyFraction() > 0.99 ) { return false; }
   if( jet.neutralEmEnergyFraction() > 0.99 ) { return false; }
   if( jet.numberOfDaughters() <=1 ) { return false; }
   if( abs( jet.eta() )  < 2.4 ){
      if( jet.chargedHadronEnergyFraction() <=0 ) { return false; }
      if( jet.chargedMultiplicity() <=0         ) { return false; }
      if( jet.chargedEmEnergyFraction() > 0.99  ) { return false; }
   }
   jetSelection->Fill(3);

   // Cleaning against primary electrons
   for( const auto& el : _electronList ){
      TLorentzVector elecVec( el.px() , el.py() , el.pz() , el.energy() );
      TLorentzVector jetVec( jet.px() , jet.py() , jet.pz() , jet.energy() );
      if( elecVec.DeltaR( jetVec ) < 0.5 ) { return false; }
   }
   jetSelection->Fill(4);

   return true;
}



//-------------------------------------------------------------------------------------------------- 
//   Helper function implementation
//--------------------------------------------------------------------------------------------------
double EventAnalyzer::mu_CRpfIso( const pat::Muon& mu ) const
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

double EventAnalyzer::el_CRpfIso( const pat::Electron& el ) const 
{
   double ans;
   double chgIso = el.pfIsolationVariables().sumChargedHadronPt ;
   double neuIso = el.pfIsolationVariables().sumNeutralHadronEt ;
   double phoIso = el.pfIsolationVariables().sumPhotonEt;
   double sumPU  = el.pfIsolationVariables().sumPUPt;
   ans  = chgIso + std::max( 0.0, neuIso + phoIso - sumPU ) ;
   ans /= el.pt();
   return ans;
}

