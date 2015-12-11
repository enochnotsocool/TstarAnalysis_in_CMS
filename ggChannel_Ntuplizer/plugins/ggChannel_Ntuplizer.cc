/*******************************************************************************
 *
 *  Filename    : ggChannel_Ntuplizer.cc
 *  Description : ggChannel_Ntuplizer for TstarAnalysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/ggChannel_Ntuplizer/interface/ggChannel_Ntuplizer.h"
#include <iostream>
using namespace std;

ggChannel_Ntuplizer::ggChannel_Ntuplizer(const edm::ParameterSet& iConfig ):
   BaseAnalyzer(iConfig),
   _hitfitter( iConfig )
{
   _hitfitBranches.registerVariables( _tree );
}

ggChannel_Ntuplizer::~ggChannel_Ntuplizer(){}

void ggChannel_Ntuplizer::beginJob() { }
void ggChannel_Ntuplizer::endJob(){}

//------------------------------------------------------------------------------ 
//   Main section
//------------------------------------------------------------------------------
void ggChannel_Ntuplizer::addCustomVariables( const edm::Event& iEvent )
{
   if( _debug > 1 ) { cerr << "\t[1] Adding custom variables" << endl ; } 
   _eventBranches.chiSqMass   = ComputeChiSqMass();
   _eventBranches.eventWeight = ComputeEventWeight( iEvent );

   RunHitFit();
}



DEFINE_FWK_MODULE(ggChannel_Ntuplizer);
