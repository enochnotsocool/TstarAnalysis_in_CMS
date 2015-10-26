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
   // Adding additional variables
   _tree->Branch( "ChiSqMass" , &_chiSqMass ); 
}

Ntuplizer::~Ntuplizer(){}

void Ntuplizer::beginJob() { }
void Ntuplizer::endJob(){}

//------------------------------------------------------------------------------ 
//   Main section
//------------------------------------------------------------------------------
void Ntuplizer::addCustomVariables( const edm::Event& )
{
   _chiSqMass = computeChiSqMass(); 
}



DEFINE_FWK_MODULE(Ntuplizer);
