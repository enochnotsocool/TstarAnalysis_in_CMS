#include "MiniMuonBranches.h"

void MiniMuonBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "MuonPt" , &_PtList );
   tree->SetBranchAddress( "MuonEta" , &_EtaList );
   tree->SetBranchAddress( "MuonPhi" , &_PhiList );
   tree->SetBranchAddress( "MuonEnergy" , &_EnergyList );
   tree->SetBranchAddress( "MuontrackRelIso" , &_trackRelIsoList );
}

