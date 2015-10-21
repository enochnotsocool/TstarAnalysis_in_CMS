#include "TstarAnalysis/RootFormat/interface/MiniMuonBranches.h"

void MiniMuonBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "MuonVec" , &_VecList , 32000 , 0 );
   tree->Branch( "MuontrackRelIso" , &_trackRelIsoList , 32000 , 0 );
}

void MiniMuonBranches::clear()
{
   
   _VecList.clear();
   _trackRelIsoList.clear();
}
