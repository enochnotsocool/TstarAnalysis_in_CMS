#include "TstarAnalysis/RootFormat/interface/MiniElectronBranches.h"

void MiniElectronBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "ElectronPt" , &_PtList , 32000 , 0 );
   tree->Branch( "ElectronEta" , &_EtaList , 32000 , 0 );
   tree->Branch( "ElectronPhi" , &_PhiList , 32000 , 0 );
   tree->Branch( "ElectronEnergy" , &_EnergyList , 32000 , 0 );
}

void MiniElectronBranches::clear()
{
   
   _PtList.clear();
   _EtaList.clear();
   _PhiList.clear();
   _EnergyList.clear();
}
