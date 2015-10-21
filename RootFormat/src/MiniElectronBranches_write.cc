#include "TstarAnalysis/RootFormat/interface/MiniElectronBranches.h"

void MiniElectronBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "ElectronVec" , &_VecList , 32000 , 0 );
}

void MiniElectronBranches::clear()
{
   
   _VecList.clear();
}
