/*******************************************************************************
 *
 *  Filename    : Ntuplizer.cc
 *  Description : Ntuplizer for TstarAnalysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/Ntuplizer/interface/Ntuplizer.h"

Ntuplizer::Ntuplizer(const edm::ParameterSet& iConfig):
   BaseAnalyzer(iConfig)
{

}

Ntuplizer::~Ntuplizer(){}

void Ntuplizer::beginJob() { }
void Ntuplizer::endJob(){}

//------------------------------------------------------------------------------ 
//   Main section
//------------------------------------------------------------------------------
void Ntuplizer::addCustomVariables( const edm::Event& iEvent )
{
   _eventBranches._chiSqMass = computeChiSqMass();
   _eventBranches._eventWeight = computeEventWeight( iEvent );
   if( _genHandle.isValid() ){
      _eventBranches._generatorWeight = _genHandle->weight();
   }
}



DEFINE_FWK_MODULE(Ntuplizer);
