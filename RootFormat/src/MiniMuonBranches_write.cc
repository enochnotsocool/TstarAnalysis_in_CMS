#include "TstarAnalysis/RootFormat/interface/MiniMuonBranches.h"

void MiniMuonBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "MuonPt" , &Pt );
   tree->Branch( "MuonEta" , &Eta );
   tree->Branch( "MuonPhi" , &Phi );
   tree->Branch( "MuonEnergy" , &Energy );
   tree->Branch( "MuontrackRelIso" , &trackRelIso );
}

void MiniMuonBranches::clear()
{
   
   Pt.clear();
   Eta.clear();
   Phi.clear();
   Energy.clear();
   trackRelIso.clear();
}
