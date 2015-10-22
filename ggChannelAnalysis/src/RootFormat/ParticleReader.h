/*******************************************************************************
 *
 *  Filename    : ParticleReader.h
 *  Description : Definition of global variables for particle reading
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  The functions are defined by in ParticleReader.cc
 *
*******************************************************************************/
#include "TChain.h"
#include "MiniJetBranches.h"
#include "MiniMuonBranches.h"
#include "MiniEventBranches.h"
#include "MiniElectronBranches.h"

extern MiniJetBranches      JetBranches; 
extern MiniMuonBranches     MuonBranches;
extern MiniEventBranches    EventBranches;
extern MiniElectronBranches ElectronBranches;

void SetInputTree( TTree* );
