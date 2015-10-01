/*******************************************************************************
 *
 *  Filename    : JetSelection.cc
 *  Description : Selection criteria for jets
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : The selection criteria follow that of TOP-15-005
 *                Loose jet ID could be found at:
 *
*******************************************************************************/
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TLorentzVector.h"

typedef std::vector<reco::GsfElectron*>  ElecList ;
typedef std::vector<pat::Muon*> MuonList;
bool isSelcJet( const pat::Jet& , const ElecList& els , const MuonList& mus )
{
   if( jet->pt() < 25.0 ) { return false; }
   if( abs( jet->eta() ) > 2.4 ) { return false; }

   // Loose JetID 
   if( jet->neutralHadronEnergyFraction() > 0.99 ) { return false; }
   if( jet->neutralEmEnergyFraction()     > 0.99 ) { return false; }
   if( jet->numberOfDaughters() <=1 ) { return false; }
   if( abs( jet->eta() )  < 2.4 ){
      if( jet->chargedHadronEnergyFraction() <=0 ) { return false; }
      if( jet->chargedMultiplicity() <=0         ) { return false; }
      if( jet->chargedEmEnergyFraction() > 0.99  ) { return false; }
   }

   // Cleaning against primary electrons
      TLorentzVector jetVec( jet.px() , jet.py() , jet.pz() , jet.energy() );
   for( const auto& el : els ){
      TLorentzVector elecVec( el->px() , el->py() , el->pz() , el->energy() );
      if( elecVec.DeltaR( jetVec ) < 0.4 ) { return false; }
   }
   for( const auto& mu : mus ){
      TLorentzVector muVec( mu->px() , mu->py() , mu->pz() , mu->energy() ) ;
      if( muVec.DeltaR( jetVec ) < 0.4 ) { return false; }  
   }

   return true;
}
