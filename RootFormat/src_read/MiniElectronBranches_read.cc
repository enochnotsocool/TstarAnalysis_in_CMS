#include "MiniElectronBranches.h"

void MiniElectronBranches::retrieveVariables( TTree* ){
   
   tree->SetBranchAddress( "ElectronVec" , &_VecList );
}

// Global Variable access
MiniElectronBranches PARTICLEBranches;
