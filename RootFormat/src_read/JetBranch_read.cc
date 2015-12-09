#include "JetBranches.h"

void JetBranches::retrieveVariables( TTree* tree )
{

   tree->SetBranchAddress( "Jet.Size", &Size );
   tree->SetBranchAddress( "Jet.Pt", Pt );
   tree->SetBranchAddress( "Jet.Eta", Eta );
   tree->SetBranchAddress( "Jet.Phi", Phi );
   tree->SetBranchAddress( "Jet.Energy", Energy );
   tree->SetBranchAddress( "Jet.BTag", BTag );
}


