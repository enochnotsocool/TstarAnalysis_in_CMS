#include "TstarAnalysis/RootFormat/interface/EventBranches.h"

void EventBranches::retrieveVariables( TTree* tree )
{

   tree->SetBranchAddress( "Event.RunNumber", &RunNumber );
   tree->SetBranchAddress( "Event.LumiNumber", &LumiNumber );
   tree->SetBranchAddress( "Event.EventNumber", &EventNumber );
   tree->SetBranchAddress( "Event.BunchCrossingNumber", &BunchCrossingNumber );
   tree->SetBranchAddress( "Event.pileUp", &pileUp );
   tree->SetBranchAddress( "Event.MET", &MET );
   tree->SetBranchAddress( "Event.METPhi", &METPhi );
   tree->SetBranchAddress( "Event.eventWeight", &eventWeight );
   tree->SetBranchAddress( "Event.chiSqMass", &chiSqMass );
}


