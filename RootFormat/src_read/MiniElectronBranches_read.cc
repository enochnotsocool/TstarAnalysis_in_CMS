#include "MiniElectronBranches.h"

void MiniElectronBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "ElectronVec" , &_VecList );
}

