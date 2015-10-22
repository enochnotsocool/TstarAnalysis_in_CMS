#include "MiniMuonBranches.h"

void MiniMuonBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "MuonVec" , &_VecList );
   tree->SetBranchAddress( "MuontrackRelIso" , &_trackRelIsoList );
}

// Global Variable access
MiniMuonBranches MuonBranches;
