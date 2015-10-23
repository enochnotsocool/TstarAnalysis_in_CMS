#include "MiniJetBranches.h"

void MiniJetBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "JetPt" , &_PtList );
   tree->SetBranchAddress( "JetEta" , &_EtaList );
   tree->SetBranchAddress( "JetPhi" , &_PhiList );
   tree->SetBranchAddress( "JetEnergy" , &_EnergyList );
}

