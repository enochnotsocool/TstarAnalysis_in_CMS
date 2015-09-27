/*******************************************************************************
 *
 *  Filename    : ggChannelFilter_Selection.cc
 *  Description : Physical object selection criterias
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/ggChannelFilter/interface/ggChannelFilter.h"

#include <iostream>
#include "TLorentzVector.h"
//------------------------------------------------------------------------------ 
//   Helper Macros
//------------------------------------------------------------------------------
#define GETLIST(  NAME , SRC )\
   edm::Handle<edm::View<NAME>> NAME ## Handle ;\
   iEvent.getByLabel( SRC , NAME ## Handle  ) ; \
   const edm::View<NAME>& NAME ## List = *( NAME ## Handle.product() );

bool ggChannelFilter::getPrimaryVertex( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   using namespace reco;

   bool gotPV = false;
   GETLIST( Vertex , _vertexsrc ) ; 
   for( const auto vertex : VertexList ){
      if( !gotPV && isGoodPV( &vertex ) ){
         _primaryVertex = vertex ;
         gotPV=true;
         break;
      }
   }
   return gotPV;
}


bool ggChannelFilter::passMuonCleaning( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   using namespace pat;

   GETLIST( Muon , _muonsrc ) ;
   for( const auto& muon : MuonList ){
      if( isTightMuon( &muon ) ){
         _tightMuonList.push_back( &muon );
      }else if( isLooseMuon( &muon ) ){
         _looseMuonList.push_back( &muon ) ;
      } 
   }
   return true;   
}

bool ggChannelFilter::passElectronCleaning( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   using namespace pat;
   GETLIST( Electron , _elecsrc );
   for( const auto& elec : ElectronList ){
      if( isTightElec( &elec )){
         _tightElecList.push_back( &elec );
      }else if( isLooseElec( &elec ) ) {
         _looseElecList.push_back( &elec );
      }
   }
   return true;
}

bool ggChannelFilter::passJetCleaning( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   using namespace pat;
   GETLIST( Jet , _jetsrc );
   for( const auto& jet : JetList ){
      if( isLooseJet( &jet ) ){
         _looseJetList.push_back( &jet );
      }
   }
   return true;
}

bool ggChannelFilter::passEventSelection( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   if( _tightMuonList.size() == 1 ){
      if( !_looseMuonList.empty() || 
          !_looseElecList.empty() ||
          !_tightElecList.empty() ) { 
         return false; }
   } else if( _tightElecList.size() == 1 ){
      if( !_looseMuonList.empty()  ||
          !_looseElecList.empty()  ||
          !_tightMuonList.empty() ) {
         return false; }
   } else { 
      return false; }
   if( _looseJetList.size() < 6 ) {
      return false;
   } else {
      if( _looseJetList[0]->pt() < 55. ) { return false; }
      if( _looseJetList[0]->pt() < 45. ) { return false; }
      if( _looseJetList[2]->pt() < 35. ) { return false; }
      unsigned int btag_count = 0 ;
      for( const auto jet : _looseJetList ){
         if( jet->bDiscriminator("combinedSecondaryVertexBJetTags") > 0.679 ){
            btag_count++; }
      }
      if( btag_count < 1 ) { return false; }
   } 
   return true;
}

//------------------------------------------------------------------------------ 
//   Object selection functions
//------------------------------------------------------------------------------

//----- Helper extended variables  ---------------------------------------------
float CRpfIso( const pat::Muon* );
float CRpfIso( const pat::Electron* );

//----- filter functions  ------------------------------------------------------
bool ggChannelFilter::isGoodPV( const reco::Vertex*  v ) const
{
   if( v->isFake() ) { return false; }
   if( v->ndof() < 4 ) { return false; } 
   if( v->z() >=24 ) { return false; }
   if( v->position().Rho() >=2  ) { return false; }
   return true;
}

bool ggChannelFilter::isLooseMuon( const pat::Muon* mu ) const 
{
   if( !muon::isLooseMuon( *mu ) ){ return false; } 
   if( mu->pt() < 10 ) { return false; }
   if( abs( mu->eta() ) < 2.5 ) { return false; } 
   if( CRpfIso( mu ) > 0.2 ) { return false; }
   return true;
}

bool ggChannelFilter::isTightMuon( const pat::Muon* mu ) const 
{
   if( !muon::isTightMuon( *mu, _primaryVertex ) ) { return false; }
   if( mu->pt()         < 20 ) { return false ; }
   if( abs( mu->eta() ) > 2.1) { return false ; }
   if( CRpfIso( mu )  > 0.12 ) { return false ; }
   return true;
}

//----- Electron selection  ------------------------------------------------------------------------
bool ggChannelFilter::isLooseElec( const pat::Electron* el ) const 
{
   if( el->pt() < 20 ) { return false; }
   if( abs(el->eta()) > 2.5) { return false; } 
   // if(  MVA < 0.0 ) { return false; }
   if( CRpfIso( el ) > 1.5 ) { return false; } 
   return true;   
}

bool ggChannelFilter::isTightElec( const pat::Electron* el )  const
{
   if( el->pt() < 30 ) { return false; }
   if( abs(el->eta()) > 1.5 ) { return false; } 
   if( abs(el->eta()) > 1.4442 && abs(el->eta()) < 1.566 ) { return false; }
   if( el->gsfTrack()->dxy( _primaryVertex.position() ) >= 0.2 ) { return false; }
   // if( MVA < 0.5 ) { return false; }
   // conversion photon
   if( CRpfIso( el ) >= 0.1 ) { return false; }
   return true;
}

bool ggChannelFilter::isLooseJet( const pat::Jet* jet ) const 
{
   if( jet->pt() < 30.0 ) { return false; }
   if( abs( jet->eta() ) > 2.5 ) { return false; }

   // Loose JetID 
   if( jet->neutralHadronEnergyFraction() > 0.99 ) { return false; }
   if( jet->neutralEmEnergyFraction() > 0.99 ) { return false; }
   if( jet->numberOfDaughters() <=1 ) { return false; }
   if( abs( jet->eta() )  < 2.4 ){
      if( jet->chargedHadronEnergyFraction() <=0 ) { return false; }
      if( jet->chargedMultiplicity() <=0         ) { return false; }
      if( jet->chargedEmEnergyFraction() > 0.99  ) { return false; }
   }

   // Cleaning against primary electrons
   for( const auto& el : _tightElecList ){
      TLorentzVector elecVec( el->px() , el->py() , el->pz() , el->energy() );
      TLorentzVector jetVec( jet->px() , jet->py() , jet->pz() , jet->energy() );
      if( elecVec.DeltaR( jetVec ) < 0.5 ) { return false; }
   }

   return true;

}

//----- Extended variables implementation  -------------------------------------
float CRpfIso( const pat::Muon* mu )
{
   double ans ;
   double chgIso = mu->pfIsolationR04().sumChargedHadronPt ;
   double neuIso = mu->pfIsolationR04().sumNeutralHadronEt ;
   double phoIso = mu->pfIsolationR04().sumPhotonEt;
   double sumPU  = mu->pfIsolationR04().sumPUPt;

   ans  = chgIso + std::max( 0. , neuIso + phoIso - 0.5*sumPU ) ;
   ans /= mu->pt();
   return ans;
}
float CRpfIso( const pat::Electron* el )
{
   double ans;
   double chgIso = el->pfIsolationVariables().sumChargedHadronPt ;
   double neuIso = el->pfIsolationVariables().sumNeutralHadronEt ;
   double phoIso = el->pfIsolationVariables().sumPhotonEt;
   double sumPU  = el->pfIsolationVariables().sumPUPt;
   ans  = chgIso + std::max( 0.0, neuIso + phoIso - sumPU ) ;
   ans /= el->pt();
   return ans;
}


