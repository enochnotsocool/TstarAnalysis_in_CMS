/*******************************************************************************
 *
 *  Filename    : MiniElectron.cc
 *  Description : Minimal implementation for electron
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifdef CMSSW
#include "TstarAnalysis/RootFormat/interface/MiniElectron.h"
#else
#include "MiniElectron.h"
#endif
MiniElectron::MiniElectron() {}
MiniElectron::~MiniElectron() {}

#ifdef CMSSW
void MiniElectron::MakeMiniElectron( const reco::GsfElectron& el )
{
   _p4.SetPtEtaPhiE( el.pt(), el.eta(), el.phi(), el.energy() );
}
#endif 

