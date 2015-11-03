#include "MiniMuonBranches.h"

void MiniMuonBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "MuonPt" , &PtPtr );
   tree->SetBranchAddress( "MuonEta" , &EtaPtr );
   tree->SetBranchAddress( "MuonPhi" , &PhiPtr );
   tree->SetBranchAddress( "MuonEnergy" , &EnergyPtr );
   tree->SetBranchAddress( "MuontrackRelIso" , &trackRelIsoPtr );
}


