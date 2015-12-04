/*******************************************************************************
 *
 *  Filename    : MuonSelection.cc
 *  Description : Muon selection implementations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TH1F.h"
#include "TstarAnalysis/BaseClasses/interface/Utils.h"
#include "TstarAnalysis/BaseClasses/interface/ObjectSelection.h"


bool ObjectSelection::isVetoMuon( const pat::Muon& mu , TH1F* hist  ) const
{
   int i = 0;
   FillHistAtBin( hist , i );
   if( !muon::isLooseMuon( mu ) ){ return false; } 
   FillHistAtBin( hist , i );
   if( mu.pt() < fMuon_Veto_Minimum_Pt ) { return false; }
   FillHistAtBin( hist , i );
   if( abs( mu.eta() ) > fMuon_Veto_Maximum_Eta ) { return false; } 
   FillHistAtBin( hist , i );
   if( mu.trackIso() /mu.pt()  > fMuon_Veto_Maximum_Isolation ) { return false; }
   FillHistAtBin( hist , i );
   return true;
}

bool ObjectSelection::isSelectionMuon( const pat::Muon& mu , const reco::Vertex& pv , TH1F* hist ) const
{
   int i = 0 ;
   FillHistAtBin( hist , i );
   if( !muon::isTightMuon( mu, pv ) ) { return false; }
   FillHistAtBin( hist , i );
   if( mu.pt() < fMuon_Minimum_Pt ) { return false ; }
   FillHistAtBin( hist , i );
   if( abs(mu.eta())  > fMuon_Maximum_Eta ) { return false ; }
   FillHistAtBin( hist , i );
   if( mu.trackIso() / mu.pt() > fMuon_Maximum_Isolation ) { return false ; }
   return true;
}


