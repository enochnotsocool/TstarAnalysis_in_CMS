#include "MiniEventBranches.h"

void MiniEventBranches::retrieveVariables( TTree* tree ){
   
   tree->SetBranchAddress( "EventRunNumber" , &_RunNumber );
   tree->SetBranchAddress( "EventLumiNumber" , &_LumiNumber );
   tree->SetBranchAddress( "EventEventNumber" , &_EventNumber );
   tree->SetBranchAddress( "EventBunchCrossingNumber" , &_BunchCrossingNumber );
   tree->SetBranchAddress( "EventpileUp" , &_pileUp );
   tree->SetBranchAddress( "EventMuonCount" , &_MuonCount );
   tree->SetBranchAddress( "EventElectronCount" , &_ElectronCount );
   tree->SetBranchAddress( "EventJetCount" , &_JetCount );
   tree->SetBranchAddress( "EventVertexCount" , &_VertexCount );
   tree->SetBranchAddress( "EventMET" , &_MET );
   tree->SetBranchAddress( "EventMETPhi" , &_METPhi );
   tree->SetBranchAddress( "EventeventWeight" , &_eventWeight );
   tree->SetBranchAddress( "EventgeneratorWeight" , &_generatorWeight );
   tree->SetBranchAddress( "EventchiSqMass" , &_chiSqMass );
}


