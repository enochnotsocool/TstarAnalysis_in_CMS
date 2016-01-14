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
   _chisqSolver(iConfig),
   _hitfitter( iConfig ),
   _runChiSq( iConfig.getParameter<bool>("RunChiSquare" ) ),
   _runHitFit(iConfig.getParameter<bool>("RunHitFit" ) )
{
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

   _event->SetTotalWeight( ComputeEventWeight(iEvent) );
   
   
   _chisqSolver.ClearAll();
   if( _runChiSq ){ RunChiSquare(); }

   _hitfitter.ClearAll();
   if( _runHitFit ){ RunHitFit(); }
}



DEFINE_FWK_MODULE(ggChannel_Ntuplizer);
