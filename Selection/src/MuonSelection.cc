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
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

bool isVetoMuon( const pat::Muon& mu )
{
   if( !muon::isLooseMuon( mu ) ){ return false; } 
   if( mu.pt() < 15 ) { return false; }
   if( abs( mu.eta() ) < 2.4 ) { return false; } 
   if( mu.trackIso()  > 0.1 ) { return false; }
   return true;
}

bool isSelcMuon( const pat::Muon& mu , const reco::Vertex& pv )
{
   if( !muon::isTightMuon( mu, pv ) ) { return false; }
   if( mu.pt()        < 30 ) { return false ; }
   if( abs(mu.eta())  > 2.1) { return false ; }
   if( mu.trackIso()  > 0.05 ) { return false ; }
   return true;
}

