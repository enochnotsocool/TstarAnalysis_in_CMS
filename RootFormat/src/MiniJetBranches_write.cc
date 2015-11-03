#include "TstarAnalysis/RootFormat/interface/MiniJetBranches.h"

void MiniJetBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "JetPt" , &Pt );
   tree->Branch( "JetEta" , &Eta );
   tree->Branch( "JetPhi" , &Phi );
   tree->Branch( "JetEnergy" , &Energy );
   tree->Branch( "Jetbtag" , &btag );
}

void MiniJetBranches::clear()
{
   
   Pt.clear();
   Eta.clear();
   Phi.clear();
   Energy.clear();
   btag.clear();
}
