#include "TstarAnalysis/RootFormat/interface/MiniJetBranches.h"

void MiniJetBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "JetPt" , &_PtList , 32000 , 0 );
   tree->Branch( "JetEta" , &_EtaList , 32000 , 0 );
   tree->Branch( "JetPhi" , &_PhiList , 32000 , 0 );
   tree->Branch( "JetEnergy" , &_EnergyList , 32000 , 0 );
}

void MiniJetBranches::clear()
{
   
   _PtList.clear();
   _EtaList.clear();
   _PhiList.clear();
   _EnergyList.clear();
}
