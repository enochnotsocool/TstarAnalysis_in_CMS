#include "DataFormats/PatCandidates/interface/Electron.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

bool isVetoElectron( 
      const reco::GsfElectron& el , 
      const edm::Handle<reco::ConversionCollection>& conversions, 
      const reco::BeamSpot& beamspot,
      const edm::Handle<reco::VertexCollection>& vtxs,
      const double &rho, 
      ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget)
{
   if( el.pt() < 15 ) { return false; }
   if( abs(el.eta()) > 2.4 ) { return false; } 
   if( abs(el.eta()) > 1.44 && abs(el.eta()) < 1.57 ){ return false ; }
   return EgammaCutBasedEleId::PassWP(
         EgammaCutBasedEleId::LOOSE,
         el,
         conversions,
         beamspot,
         vtxs,
         el.pfIsolationVariables().sumChargedHadronPt,
         el.pfIsolationVariables().sumPhotonEt,
         el.pfIsolationVariables().sumNeutralHadronEt,
         rho,
         EAtarget) ; 
}

bool isSelcElectron( 
      const reco::GsfElectron& el , 
      const edm::Handle<reco::ConversionCollection>& conversions, 
      const reco::BeamSpot& beamspot,
      const edm::Handle<reco::VertexCollection>& vtxs,
      const double &rho, 
      ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget)
{
   if( el.pt() < 30 ) { return false; }
   if( abs(el.eta()) > 2.1 ) { return false; } 
   if( abs(el.eta()) > 1.44 && abs(el.eta()) < 1.57 ){ return false ; }
   return EgammaCutBasedEleId::PassWP(
         EgammaCutBasedEleId::MEDIUM,
         el,
         conversions,
         beamspot,
         vtxs,
         el.pfIsolationVariables().sumChargedHadronPt,
         el.pfIsolationVariables().sumPhotonEt,
         el.pfIsolationVariables().sumNeutralHadronEt,
         rho,
         EAtarget) ; 
}


////----- Helper extended variables  ---------------------------------------------
//float CRpfIso( const pat::Muon* );
//float CRpfIso( const pat::Electron* );
//
////----- filter functions  ------------------------------------------------------
//
//bool isLooseMuon( const pat::Muon* mu ) const 
//{
//   if( !muon::isLooseMuon( *mu ) ){ return false; } 
//   if( mu->pt() < 15 ) { return false; }
//   if( abs( mu->eta() ) < 2.4 ) { return false; } 
//   if( CRpfIso( mu ) > 0.1 ) { return false; }
//   return true;
//}
//
//bool isTightMuon( const pat::Muon* mu ) const 
//{
//   muonCount[0]++;
//   if( !muon::isTightMuon( *mu, _primaryVertex ) ) { return false; }
//   muonCount[1]++;
//   if( mu->pt()         < 30 ) { return false ; }
//   if( abs( mu->eta() ) > 2.1) { return false ; }
//   muonCount[2]++;
//   if( CRpfIso( mu )  > 0.05 ) { return false ; }
//   muonCount[3]++;
//   return true;
//}
//
////----- Electron selection  ------------------------------------------------------------------------
//bool isLooseElec( const edm::Ptr<reco::GsfElectron>& el ) const 
//{
//   return true;   
//}
//
//bool isTightElec( const edm::Ptr<reco::GsfElectron>& el )  const
//{
//   elecCount[0]++;
//   if( el->pt() < 30 ) { return false; }
//   elecCount[1]++;
//   if( abs(el->eta()) > 2.1 ) { return false; } 
//   if( abs(el->eta()) > 1.44&& abs(el->eta()) < 1.57 ) { return false; }
//   elecCount[2]++;
//   if( ! (*mediumIDs)[el] ) { return false; }
//   elecCount[4]++;
//   return true;
//}
//
//bool isLooseJet( const pat::Jet* jet ) const 
//{
//   if( jet->pt() < 25.0 ) { return false; }
//   if( abs( jet->eta() ) > 2.4 ) { return false; }
//
//   // Loose JetID 
//   if( jet->neutralHadronEnergyFraction() > 0.99 ) { return false; }
//   if( jet->neutralEmEnergyFraction() > 0.99 ) { return false; }
//   if( jet->numberOfDaughters() <=1 ) { return false; }
//   if( abs( jet->eta() )  < 2.4 ){
//      if( jet->chargedHadronEnergyFraction() <=0 ) { return false; }
//      if( jet->chargedMultiplicity() <=0         ) { return false; }
//      if( jet->chargedEmEnergyFraction() > 0.99  ) { return false; }
//   }
//
//   // Cleaning against primary electrons
//   for( const auto& el : _selcElecList ){
//      TLorentzVector elecVec( el->px() , el->py() , el->pz() , el->energy() );
//      TLorentzVector jetVec( jet->px() , jet->py() , jet->pz() , jet->energy() );
//      if( elecVec.DeltaR( jetVec ) < 0.5 ) { return false; }
//   }
//
//   return true;
//
//}
//
////----- Extended variables implementation  -------------------------------------
//float CRpfIso( const pat::Muon* mu )
//{
//   double ans ;
//   double chgIso = mu->pfIsolationR04().sumChargedHadronPt ;
//   double neuIso = mu->pfIsolationR04().sumNeutralHadronEt ;
//   double phoIso = mu->pfIsolationR04().sumPhotonEt;
//   double sumPU  = mu->pfIsolationR04().sumPUPt;
//
//   ans  = chgIso + std::max( 0. , neuIso + phoIso - 0.5*sumPU ) ;
//   ans /= mu->pt();
//   return ans;
//}
//float CRpfIso( const pat::Electron* el )
//{
//   double ans;
//   double chgIso = el->pfIsolationVariables().sumChargedHadronPt ;
//   double neuIso = el->pfIsolationVariables().sumNeutralHadronEt ;
//   double phoIso = el->pfIsolationVariables().sumPhotonEt;
//   double sumPU  = el->pfIsolationVariables().sumPUPt;
//   ans  = chgIso + std::max( 0.0, neuIso + phoIso - sumPU ) ;
//   ans /= el->pt();
//   return ans;
//}
//
//
//
