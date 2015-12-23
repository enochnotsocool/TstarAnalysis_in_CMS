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
   if( _runChiSq ){
      _chisqResult  = new ChiSquareResult;
      _tree->Branch( "ChiSquareResult" , "ChiSquareResult" , &_chisqResult , 32000 , 99 );
   }
   if( _runHitFit ){
      _hitfitResult = new HitFitResult;
      _tree->Branch( "HitFitResult", "HitFitResult", &_hitfitResult, 32000, 99 );
   }
}

ggChannel_Ntuplizer::~ggChannel_Ntuplizer(){}

void ggChannel_Ntuplizer::beginJob() { }
void ggChannel_Ntuplizer::endJob(){}

//------------------------------------------------------------------------------ 
//   Main section
//------------------------------------------------------------------------------
void ggChannel_Ntuplizer::addCustomVariables( const edm::Event& iEvent )
{
   _chisqSolver.ClearAll();
   _hitfitter.ClearAll();
   if( _debug > 1 ) { cerr << "\t[1] Adding custom variables" << endl ; } 
   //_eventBranches.eventWeight = ComputeEventWeight( iEvent );

   RunChiSquare();
   RunHitFit(); 
}



DEFINE_FWK_MODULE(ggChannel_Ntuplizer);
