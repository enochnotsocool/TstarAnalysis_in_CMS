/*******************************************************************************
 *
 *  Filename    : ggChannel_Ntuplizer_eventWeight.cc
 *  Description : File for computing event weight
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/ggChannel_Ntuplizer/interface/ggChannel_Ntuplizer.h"
#include "TstarAnalysis/MCWeighter/interface/MCWeights.h"
#include <iostream>

float ggChannel_Ntuplizer::ComputeEventWeight( const edm::Event& iEvent )
{
   if( iEvent.isRealData() ) { return 1.0; }
   float ans = 1.0 ; 
   //----- PileUp weighting  ------------------------------------------------------
   ans *= PileUpWeight( _event->PileUp() ) ;

   return ans;
}
