/*******************************************************************************
 *
 *  Filename    : MiniMuon.h
 *  Description : Minimal implementation of muon for combine analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#ifndef __MINIMUON_H__
#define __MINIMUON_H__

#ifdef CMSSW
#include "TstarAnalysis/RootFormat/interface/MiniParticle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#else
#include "MiniParticle.h"
#endif

class MiniMuon : public MiniParticle
{
public:
   MiniMuon ();
   virtual ~MiniMuon ();

   double AbsTrackIso() const ;
   double RelTrackIso() const ;

#ifdef CMSSW
   void MakeMiniMuon( const pat::Muon& ); 
#endif

private:
   double _absTrackIso;
};

#endif // __MINIMUON_H__
