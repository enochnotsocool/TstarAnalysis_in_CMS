#include "MiniElectronBranches.h"

void MiniElectronBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "ElectronVec" , &_VecList );
}

// Global Variable access
MiniElectronBranches ElectronBranches;
