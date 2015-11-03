/*******************************************************************************
 *
 *  Filename    : MuonSelection.cc
 *  Description : Muon selection implementations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TH1F.h"
#include "TstarAnalysis/BaseClasses/interface/TypeDefs.h"
#include "TstarAnalysis/BaseClasses/interface/Limits.h"

bool isVetoMuon( const pat::Muon& mu , TH1F* hist  )
{
   if( hist!=NULL ) { hist->Fill(0); }
   if( !muon::isLooseMuon( mu ) ){ return false; } 
   if( hist!=NULL ) { hist->Fill(1); }
   if( mu.pt() < VETO_MUON_PT_LIM ) { return false; }
   if( hist!=NULL ) { hist->Fill(2); }
   if( abs( mu.eta() ) > VETO_MUON_ETA_LIM ) { return false; } 
   if( hist!=NULL ) { hist->Fill(3); }
   if( mu.trackIso() /mu.pt()  > VETO_MUON_ISO_LIM ) { return false; }
   if( hist!=NULL ) { hist->Fill(4); }
   return true;
}

bool isSelectionMuon( const pat::Muon& mu , const reco::Vertex& pv , TH1F* hist )
{
   if( hist!=NULL ) { hist->Fill(0); }
   if( !muon::isTightMuon( mu, pv ) ) { return false; }
   if( hist!=NULL ) { hist->Fill(1); }
   if( mu.pt() < SELECTED_MUON_PT_LIM ) { return false ; }
   if( hist!=NULL ) { hist->Fill(2); }
   if( abs(mu.eta())  > SELECTED_MUON_ETA_LIM) { return false ; }
   if( hist!=NULL ) { hist->Fill(3); }
   if( mu.trackIso() / mu.pt() > SELECTED_MUON_ISO_LIM ) { return false ; }
   if( hist!=NULL ) { hist->Fill(4); }
   return true;
}


