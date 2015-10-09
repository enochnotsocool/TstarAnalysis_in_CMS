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

#include "TLorentzVector.h"
#include "TstarAnalysis/Selection/interface/Counting.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

typedef std::vector<const reco::GsfElectron*>  ElecList ;
typedef std::vector<const pat::Muon*> MuonList;

bool isSelcJet( const pat::Jet& jet , const ElecList& els , const MuonList& mus, TH1F* hist, float pt_limit )
{
   HIST_COUNT(0);
   if( jet.pt() < pt_limit ) { return false; }
   HIST_COUNT(1);
   if( abs( jet.eta() ) > 2.4 ) { return false; }

   HIST_COUNT(2);
   //----- Loose Jet ID  ------------------------------------------------------------------------------
   if( jet.neutralHadronEnergyFraction() > 0.99 ) { return false; }
   if( jet.neutralEmEnergyFraction()     > 0.99 ) { return false; }
   if( jet.numberOfDaughters() <=1 ) { return false; }
   if( abs( jet.eta() )  < 2.4 ){
      if( jet.chargedHadronEnergyFraction() <=0 ) { return false; }
      if( jet.chargedMultiplicity() <=0         ) { return false; }
      if( jet.chargedEmEnergyFraction() > 0.99  ) { return false; }
   }

   HIST_COUNT(3);
   //----- Cleaning against selected leptons  ---------------------------------------------------------
   TLorentzVector jetVec( jet.px() , jet.py() , jet.pz() , jet.energy() );
   for( const auto& el : els ){
      TLorentzVector elecVec( el->px() , el->py() , el->pz() , el->energy() );
      if( elecVec.DeltaR( jetVec ) < 0.4 ) { return false; }
   }
   for( const auto& mu : mus ){
      TLorentzVector muVec( mu->px() , mu->py() , mu->pz() , mu->energy() ) ;
      if( muVec.DeltaR( jetVec ) < 0.4 ) { return false; }  
   }
   HIST_COUNT(4);
   return true;
}
