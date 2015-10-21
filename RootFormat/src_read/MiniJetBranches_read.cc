#include "MiniJetBranches.h"

void MiniJetBranches::retrieveVariables( TTree* ){
   
   tree->SetBranchAddress( "JetVec" , &_VecList );
   tree->SetBranchAddress( "Jettemp" , &_tempList );
}

// Global Variable access
MiniJetBranches PARTICLEBranches;
