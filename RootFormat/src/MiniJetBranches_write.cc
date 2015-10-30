#include "TstarAnalysis/RootFormat/interface/MiniJetBranches.h"

void MiniJetBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "JetPt" , &_PtList );
   tree->Branch( "JetEta" , &_EtaList );
   tree->Branch( "JetPhi" , &_PhiList );
   tree->Branch( "JetEnergy" , &_EnergyList );
   tree->Branch( "Jetbtag" , &_btagList );
}

void MiniJetBranches::clear()
{
   
   _PtList.clear();
   _EtaList.clear();
   _PhiList.clear();
   _EnergyList.clear();
   _btagList.clear();
}
