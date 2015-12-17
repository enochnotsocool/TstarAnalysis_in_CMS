#include "TstarAnalysis/RootFormat/interface/ElectronBranches.h"

void ElectronBranches::retrieveVariables( TTree* tree )
{

   tree->SetBranchAddress( "Electron.Size", &Size );
   tree->SetBranchAddress( "Electron.Pt", Pt );
   tree->SetBranchAddress( "Electron.Eta", Eta );
   tree->SetBranchAddress( "Electron.Phi", Phi );
   tree->SetBranchAddress( "Electron.Energy", Energy );
}


