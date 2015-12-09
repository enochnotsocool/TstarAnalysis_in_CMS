#include "TstarAnalysis/RootFormat/interface/MuonBranches.h"

void MuonBranches::registerVariables( TTree* tree )
{

   tree->Branch( "Muon.Size", &Size, "Muon.Size/i" );
   tree->Branch( "Muon.Pt", Pt, "Muon.Pt[Muon.Size]/F" );
   tree->Branch( "Muon.Eta", Eta, "Muon.Eta[Muon.Size]/F" );
   tree->Branch( "Muon.Phi", Phi, "Muon.Phi[Muon.Size]/F" );
   tree->Branch( "Muon.Energy", Energy, "Muon.Energy[Muon.Size]/F" );
   tree->Branch( "Muon.TrackRelIso", TrackRelIso, "Muon.TrackRelIso[Muon.Size]/F" );
}

