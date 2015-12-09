#include "TstarAnalysis/RootFormat/interface/EventBranches.h"

void EventBranches::registerVariables( TTree* tree )
{

   tree->Branch( "Event.RunNumber", &RunNumber, "Event.RunNumber/i" );
   tree->Branch( "Event.LumiNumber", &LumiNumber, "Event.LumiNumber/l" );
   tree->Branch( "Event.EventNumber", &EventNumber, "Event.EventNumber/i" );
   tree->Branch( "Event.BunchCrossingNumber", &BunchCrossingNumber, "Event.BunchCrossingNumber/i" );
   tree->Branch( "Event.pileUp", &pileUp, "Event.pileUp/i" );
   tree->Branch( "Event.MET", &MET, "Event.MET/F" );
   tree->Branch( "Event.METPhi", &METPhi, "Event.METPhi/F" );
   tree->Branch( "Event.eventWeight", &eventWeight, "Event.eventWeight/F" );
   tree->Branch( "Event.chiSqMass", &chiSqMass, "Event.chiSqMass/F" );
}

