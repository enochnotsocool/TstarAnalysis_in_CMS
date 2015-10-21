#include "TstarAnalysis/RootFormat/interface/MiniJetBranches.h"

void MiniJetBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "JetVec" , &_VecList , 32000 , 0 );
   tree->Branch( "Jettemp" , &_tempList , 32000 , 0 );
}

void MiniJetBranches::clear()
{
   
   _VecList.clear();
   _tempList.clear();
}
