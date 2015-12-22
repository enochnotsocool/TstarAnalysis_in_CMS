/*******************************************************************************
 *
 *  Filename    : MiniJet.h
 *  Description : Minimal implementation of jets for combine analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __MINIJET_H__
#define __MINIJET_H__

#ifdef CMSSW
#include "TstarAnalysis/RootFormat/interface/MiniParticle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#else
#include "MiniParticle.h"
#endif

class MiniJet : public MiniParticle
{
public:
   MiniJet();
   virtual ~MiniJet ();

   double Btag();

#ifdef CMSSW
   void MakeMiniJet( const pat::Jet& );
#endif

private:
   double _btag;
};

#endif // __MINIJET_H__
