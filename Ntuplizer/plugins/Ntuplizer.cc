/*******************************************************************************
 *
 *  Filename    : Ntuplizer.cc
 *  Description : Ntuplizer for TstarAnalysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/Ntuplizer/interface/Ntuplizer.h"
#include <iostream>
using namespace std;

Ntuplizer::Ntuplizer(const edm::ParameterSet& iConfig ):
   BaseAnalyzer(iConfig)
{
   if( _debug ) { cerr << "Spawning instance of Ntuplizer" << endl; }
   InitHitFit( iConfig );
}

Ntuplizer::~Ntuplizer(){}

void Ntuplizer::beginJob() { }
void Ntuplizer::endJob(){}

//------------------------------------------------------------------------------ 
//   Main section
//------------------------------------------------------------------------------
void Ntuplizer::addCustomVariables( const edm::Event& iEvent )
{
   if( _debug > 1 ) { cerr << "\t[1] Adding custom variables" << endl ; } 
   _eventBranches._chiSqMass = ComputeChiSqMass();
   _eventBranches._eventWeight = ComputeEventWeight( iEvent );
   if( _genHandle.isValid() ){
      _eventBranches._generatorWeight = _genHandle->weight();
   }

   RunHitFit( iEvent );
   AddHitFitResults();
}



DEFINE_FWK_MODULE(Ntuplizer);
