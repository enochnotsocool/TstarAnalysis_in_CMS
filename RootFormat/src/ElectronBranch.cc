#include "TstarAnalysis/RootFormat/interface/ElectronBranches.h"

void ElectronBranches::registerVariables( TTree* tree )
{

   tree->Branch( "Electron.Size", &Size, "Electron.Size/i" );
   tree->Branch( "Electron.Pt", Pt, "Electron.Pt[Electron.Size]/F" );
   tree->Branch( "Electron.Eta", Eta, "Electron.Eta[Electron.Size]/F" );
   tree->Branch( "Electron.Phi", Phi, "Electron.Phi[Electron.Size]/F" );
   tree->Branch( "Electron.Energy", Energy, "Electron.Energy[Electron.Size]/F" );
}

