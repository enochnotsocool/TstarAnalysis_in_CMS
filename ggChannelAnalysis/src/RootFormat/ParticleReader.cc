/*******************************************************************************
 *
 *  Filename    : ParticleReader.cc
 *  Description : Global branches for fie reading
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TChain.h"
#include "MiniJetBranches.h"
#include "MiniMuonBranches.h"
#include "MiniEventBranches.h"
#include "MiniElectronBranches.h"

MiniJetBranches      JetBranches; 
MiniMuonBranches     MuonBranches;
MiniEventBranches    EventBranches;
MiniElectronBranches ElectronBranches;

void SetInputTree( TTree* x )
{
   JetBranches.retrieveVariables( x );
   MuonBranches.retrieveVariables( x );
   EventBranches.retrieveVariables( x );
   ElectronBranches.retrieveVariables( x );
}

