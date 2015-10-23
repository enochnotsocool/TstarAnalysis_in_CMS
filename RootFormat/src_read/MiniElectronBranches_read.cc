#include "MiniElectronBranches.h"

void MiniElectronBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "ElectronPt" , &_PtList );
   tree->SetBranchAddress( "ElectronEta" , &_EtaList );
   tree->SetBranchAddress( "ElectronPhi" , &_PhiList );
   tree->SetBranchAddress( "ElectronEnergy" , &_EnergyList );
}

