/*******************************************************************************
 *
 *  Filename    : MuonSelection.cc
 *  Description : Muon selection implementations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TH1F.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

bool isVetoMuon( const pat::Muon& mu , TH1F* hist  )
{
   if( hist!=NULL ) { hist->Fill(0); }
   if( !muon::isLooseMuon( mu ) ){ return false; } 
   if( hist!=NULL ) { hist->Fill(1); }
   if( mu.pt() < 15 ) { return false; }
   if( hist!=NULL ) { hist->Fill(2); }
   if( abs( mu.eta() ) > 2.4 ) { return false; } 
   if( hist!=NULL ) { hist->Fill(3); }
   if( mu.trackIso() /mu.pt()  > 0.1 ) { return false; }
   if( hist!=NULL ) { hist->Fill(4); }
   return true;
}

bool isSelectionMuon( const pat::Muon& mu , const reco::Vertex& pv , TH1F* hist )
{
   if( hist!=NULL ) { hist->Fill(0); }
   if( !muon::isTightMuon( mu, pv ) ) { return false; }
   if( hist!=NULL ) { hist->Fill(1); }
   if( mu.pt()        < 30 ) { return false ; }
   if( hist!=NULL ) { hist->Fill(2); }
   if( abs(mu.eta())  > 2.1) { return false ; }
   if( hist!=NULL ) { hist->Fill(3); }
   if( mu.trackIso() / mu.pt() > 0.05 ) { return false ; }
   if( hist!=NULL ) { hist->Fill(4); }
   return true;
}


