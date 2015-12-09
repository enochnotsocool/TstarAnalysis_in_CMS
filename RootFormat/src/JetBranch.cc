#include "TstarAnalysis/RootFormat/interface/JetBranches.h"

void JetBranches::registerVariables( TTree* tree )
{

   tree->Branch( "Jet.Size", &Size, "Jet.Size/i" );
   tree->Branch( "Jet.Pt", Pt, "Jet.Pt[Jet.Size]/F" );
   tree->Branch( "Jet.Eta", Eta, "Jet.Eta[Jet.Size]/F" );
   tree->Branch( "Jet.Phi", Phi, "Jet.Phi[Jet.Size]/F" );
   tree->Branch( "Jet.Energy", Energy, "Jet.Energy[Jet.Size]/F" );
   tree->Branch( "Jet.BTag", BTag, "Jet.BTag[Jet.Size]/F" );
}

