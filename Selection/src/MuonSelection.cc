/*******************************************************************************
 *
 *  Filename    : MuonSelection.cc
 *  Description : Selection Criteria for muons
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : Selection criteria follow those in 
 *                 [1] TOP-15-005
 *                Definition of track particle flow isolation is:
 *                 [2] https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Muon_Isolation_AN1
 *
*******************************************************************************/
#include "TstarAnalysis/Selection/interface/Counting.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

bool isVetoMuon( const pat::Muon& mu , TH1F* hist  )
{
   HIST_COUNT(0);
   if( !muon::isLooseMuon( mu ) ){ return false; } 
   HIST_COUNT(1);
   if( mu.pt() < 15 ) { return false; }
   HIST_COUNT(2);
   if( abs( mu.eta() ) < 2.4 ) { return false; } 
   HIST_COUNT(3);
   if( mu.trackIso() /mu.pt()  > 0.1 ) { return false; }
   HIST_COUNT(3);
   return true;
}

bool isSelcMuon( const pat::Muon& mu , const reco::Vertex& pv , TH1F* hist )
{
   HIST_COUNT(0);
   if( !muon::isTightMuon( mu, pv ) ) { return false; }
   HIST_COUNT(1);
   if( mu.pt()        < 30 ) { return false ; }
   HIST_COUNT(2);
   if( abs(mu.eta())  > 2.1) { return false ; }
   HIST_COUNT(3);
   if( mu.trackIso() / mu.pt() > 0.05 ) { return false ; }
   HIST_COUNT(4);
   return true;
}

