#include "TstarAnalysis/RootFormat/interface/MiniElectronBranches.h"

void MiniElectronBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "ElectronPt" , &_PtList );
   tree->Branch( "ElectronEta" , &_EtaList );
   tree->Branch( "ElectronPhi" , &_PhiList );
   tree->Branch( "ElectronEnergy" , &_EnergyList );
}

void MiniElectronBranches::clear()
{
   
   _PtList.clear();
   _EtaList.clear();
   _PhiList.clear();
   _EnergyList.clear();
}
