/*******************************************************************************
 *
 *  Filename    : MiniMuon.cc
 *  Description : Minimal muon implementations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifdef CMSSW
#include "TstarAnalysis/RootFormat/interface/MiniMuon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#else
#include "MiniMuon.h"
#endif

MiniMuon::MiniMuon(){}
MiniMuon::~MiniMuon(){}

double MiniMuon::AbsTrackIso() const { return _absTrackIso; }
double MiniMuon::RelTrackIso() const { return _absTrackIso/pt(); }


#ifdef CMSSW
void MiniMuon::MakeMiniMuon( const pat::Muon& mu )
{
   _p4.SetPtEtaPhiE( mu.pt() , mu.eta(), mu.phi() ,mu.energy() );
   _absTrackIso = mu.trackIso();
}
#endif
