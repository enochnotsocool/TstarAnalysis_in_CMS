/*******************************************************************************
 *
 *  Filename    : JetSelection.cc
 *  Description : Jet Selection implementations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TstarAnalysis/BaseClasses/interface/Utils.h"
#include "TstarAnalysis/BaseClasses/interface/ObjectSelection.h"
#include <iostream>
using namespace std;

bool ObjectSelection::isSelectionJet( const pat::Jet& jet , const MuonList& mus , const ElectronList& els, TH1F* hist )const
{
   int i = 0;
   FillHistAtBin( hist , i );
   if( jet.pt() < fJet_Minimum_Pt ) { return false; }
   FillHistAtBin( hist , i );
   if( abs( jet.eta() ) > fJet_Maximum_Eta ) { return false; }

   //----- Loose Jet ID  ------------------------------------------------------------------------------
   FillHistAtBin( hist , i );
   if( jet.neutralHadronEnergyFraction() > 0.99 ) { return false; }
   if( jet.neutralEmEnergyFraction()     > 0.99 ) { return false; }
   if( jet.numberOfDaughters() <=1 ) { return false; }
   if( abs( jet.eta() )  < 2.4 ){
      if( jet.chargedHadronEnergyFraction() <=0 ) { return false; }
      if( jet.chargedMultiplicity() <=0         ) { return false; }
      if( jet.chargedEmEnergyFraction() > 0.99  ) { return false; }
   }

   //----- Cleaning against selected leptons  ---------------------------------------------------------
   if( hist!=NULL ) { hist->Fill(3); }
   TLorentzVector jetVec( jet.px() , jet.py() , jet.pz() , jet.energy() );
   for( const auto& el : els ){
      TLorentzVector elecVec( el->px() , el->py() , el->pz() , el->energy() );
      if( elecVec.DeltaR( jetVec ) < fJet_Minimum_DeltaR ) { return false; }
   }
   for( const auto& mu : mus ){
      TLorentzVector muVec( mu->px() , mu->py() , mu->pz() , mu->energy() ) ;
      if( muVec.DeltaR( jetVec ) < fJet_Minimum_DeltaR ) { return false; }  
   } 
   if( hist!=NULL ) { hist->Fill(4); }
   return true;
}

