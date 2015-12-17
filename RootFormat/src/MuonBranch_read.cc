#include "TstarAnalysis/RootFormat/interface/MuonBranches.h"

void MuonBranches::retrieveVariables( TTree* tree )
{

   tree->SetBranchAddress( "Muon.Size", &Size );
   tree->SetBranchAddress( "Muon.Pt", Pt );
   tree->SetBranchAddress( "Muon.Eta", Eta );
   tree->SetBranchAddress( "Muon.Phi", Phi );
   tree->SetBranchAddress( "Muon.Energy", Energy );
   tree->SetBranchAddress( "Muon.TrackRelIso", TrackRelIso );
}


