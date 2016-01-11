/*******************************************************************************
 *
 *  Filename    : MiniElectron.h
 *  Description : Minimal implementation for electron for combine analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __MINIELECTRON_H__
#define __MINIELECTRON_H__

#ifdef CMSSW
#include "TstarAnalysis/RootFormat/interface/MiniParticle.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#else
#include "MiniParticle.h"
#endif

class MiniElectron : public MiniParticle
{
public:
   MiniElectron();
   virtual ~MiniElectron ();

#ifdef CMSSW
   void MakeMiniElectron( const reco::GsfElectron& );
#endif
private:
   /* data */
};


#endif // __MINIELECTRON_H__
