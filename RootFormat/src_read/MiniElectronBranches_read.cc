#include "MiniElectronBranches.h"

void MiniElectronBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "ElectronPt" , &PtPtr );
   tree->SetBranchAddress( "ElectronEta" , &EtaPtr );
   tree->SetBranchAddress( "ElectronPhi" , &PhiPtr );
   tree->SetBranchAddress( "ElectronEnergy" , &EnergyPtr );
}


