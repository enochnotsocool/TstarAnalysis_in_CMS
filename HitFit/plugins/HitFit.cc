/*******************************************************************************
 *
 *  Filename    : HitFit.cc
 *  Description : HitFit for TstarAnalysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/HitFit/interface/HitFit.h"
#include <iostream>
using namespace std;

HitFit::HitFit(const edm::ParameterSet& iConfig ):
   BaseAnalyzer(iConfig)
{
   if( _debug ) { cerr << "Spawning instance of HitFit" << endl; }
   InitHitFit( iConfig );
}

HitFit::~HitFit(){}

void HitFit::beginJob() { }
void HitFit::endJob(){}

//------------------------------------------------------------------------------ 
//   Main section
//------------------------------------------------------------------------------
void HitFit::addCustomVariables( const edm::Event& iEvent )
{
   if( _debug > 1 ) { cerr << "\t[1] Adding custom variables" << endl ; } 
   _eventBranches.chiSqMass   = ComputeChiSqMass();
   _eventBranches.eventWeight = ComputeEventWeight( iEvent );
   
   RunHitFit( iEvent );
   AddHitFitResults();
}



DEFINE_FWK_MODULE(HitFit);
