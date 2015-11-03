#include "TstarAnalysis/RootFormat/interface/MiniElectronBranches.h"

void MiniElectronBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "ElectronPt" , &Pt );
   tree->Branch( "ElectronEta" , &Eta );
   tree->Branch( "ElectronPhi" , &Phi );
   tree->Branch( "ElectronEnergy" , &Energy );
}

void MiniElectronBranches::clear()
{
   
   Pt.clear();
   Eta.clear();
   Phi.clear();
   Energy.clear();
}
