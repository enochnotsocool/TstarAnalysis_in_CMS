#include "TstarAnalysis/RootFormat/interface/MiniEventBranches.h"

void MiniEventBranches::registerVariables( TTree* tree )
{
   
   tree->Branch( "EventRunNumber" , &_RunNumber );
   tree->Branch( "EventLumiNumber" , &_LumiNumber );
   tree->Branch( "EventEventNumber" , &_EventNumber );
   tree->Branch( "EventBunchCrossingNumber" , &_BunchCrossingNumber );
   tree->Branch( "EventpileUpWeight" , &_pileUpWeight );
   tree->Branch( "EventMuonCount" , &_MuonCount );
   tree->Branch( "EventElectronCount" , &_ElectronCount );
   tree->Branch( "EventJetCount" , &_JetCount );
   tree->Branch( "EventVertexCount" , &_VertexCount );
   tree->Branch( "EventMET" , &_MET );
   tree->Branch( "EventMETPhi" , &_METPhi );
   tree->Branch( "EventchiMass" , &_chiMass );
}

void MiniEventBranches::clear()
{
   
}
