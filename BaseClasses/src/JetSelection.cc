/*******************************************************************************
 *
 *  Filename    : JetSelection.cc
 *  Description : Jet Selection implementations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TLorentzVector.h"
#include "TstarAnalysis/Selection/interface/Counting.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

typedef std::vector<const reco::GsfElectron*> ElecList;
typedef std::vector<const pat::Muon*> MuonList; 

bool isSelectionJet( const pat::Jet& jet , const MuonList& mus , const ElecList& els, TH1F* )
{
   if( jet.pt() < 30. ) { return false; }
   if( abs( jet.eta() ) > 2.4 ) { return false; }

   //----- Loose Jet ID  ------------------------------------------------------------------------------
   if( jet.neutralHadronEnergyFraction() > 0.99 ) { return false; }
   if( jet.neutralEmEnergyFraction()     > 0.99 ) { return false; }
   if( jet.numberOfDaughters() <=1 ) { return false; }
   if( abs( jet.eta() )  < 2.4 ){
      if( jet.chargedHadronEnergyFraction() <=0 ) { return false; }
      if( jet.chargedMultiplicity() <=0         ) { return false; }
      if( jet.chargedEmEnergyFraction() > 0.99  ) { return false; }
   }

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
   return true;
}

