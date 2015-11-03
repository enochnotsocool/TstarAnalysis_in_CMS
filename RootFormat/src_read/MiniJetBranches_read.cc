#include "MiniJetBranches.h"

void MiniJetBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "JetPt" , &PtPtr );
   tree->SetBranchAddress( "JetEta" , &EtaPtr );
   tree->SetBranchAddress( "JetPhi" , &PhiPtr );
   tree->SetBranchAddress( "JetEnergy" , &EnergyPtr );
   tree->SetBranchAddress( "Jetbtag" , &btagPtr );
}


