#include "MiniJetBranches.h"

void MiniJetBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "JetVec" , &_VecList );
   tree->SetBranchAddress( "Jettemp" , &_tempList );
}

