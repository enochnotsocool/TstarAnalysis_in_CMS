#include "TstarAnalysis/RootFormat/interface/MiniMuonBranches.h"

void MiniMuonBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "MuonPt" , &_PtList , 32000 , 0 );
   tree->Branch( "MuonEta" , &_EtaList , 32000 , 0 );
   tree->Branch( "MuonPhi" , &_PhiList , 32000 , 0 );
   tree->Branch( "MuonEnergy" , &_EnergyList , 32000 , 0 );
   tree->Branch( "MuontrackRelIso" , &_trackRelIsoList , 32000 , 0 );
}

void MiniMuonBranches::clear()
{
   
   _PtList.clear();
   _EtaList.clear();
   _PhiList.clear();
   _EnergyList.clear();
   _trackRelIsoList.clear();
}
