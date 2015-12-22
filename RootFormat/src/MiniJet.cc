/*******************************************************************************
 *
 *  Filename    : MiniJet.cc
 *  Description : Minimal implementation of jet
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifdef CMSSW
#include "TstarAnalysis/RootFormat/interface/MiniJet.h"
#else 
#include "MiniJet.h"
#endif

MiniJet::MiniJet() {}
MiniJet::~MiniJet() {}

double MiniJet::Btag() { return _btag; }

#ifdef CMSSW
void MiniJet::MakeMiniJet( const pat::Jet& jet )
{
   _p4.SetPtEtaPhiE( jet.pt(), jet.eta(), jet.phi(), jet.energy() );
   _btag = jet.bDiscriminator( "pfCombinedSecondaryVertexV2BJetTags" );
}
#endif
