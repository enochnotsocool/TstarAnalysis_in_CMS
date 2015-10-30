#include "TstarAnalysis/RootFormat/interface/MiniMuonBranches.h"

void MiniMuonBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "MuonPt" , &_PtList );
   tree->Branch( "MuonEta" , &_EtaList );
   tree->Branch( "MuonPhi" , &_PhiList );
   tree->Branch( "MuonEnergy" , &_EnergyList );
   tree->Branch( "MuontrackRelIso" , &_trackRelIsoList );
}

void MiniMuonBranches::clear()
{
   
   _PtList.clear();
   _EtaList.clear();
   _PhiList.clear();
   _EnergyList.clear();
   _trackRelIsoList.clear();
}
