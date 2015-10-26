/*******************************************************************************
 *
 *  Filename    : Sample_BasicPlot.cc
 *  Description : Implementation of basic plots 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "SampleInfo.h"
#include "MiniEventBranches.h"
#include "MiniJetBranches.h"
#include "MiniMuonBranches.h"
#include "MiniElectronBranches.h"

static MiniEventBranches    eventBranches;
static MiniJetBranches      jetBranches;
static MiniMuonBranches     muonBranches;
static MiniElectronBranches elecBranches;

void SetInputTree( TTree* );

void SampleInfo::makeBasicPlots()
{
   printf( "Making basic plots for %s\n", _name.c_str() );
  
   SetInputTree( _chain );
   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      _chain->GetEntry(i);
      printf( "\r[%s] Event %lld/%lld.... " , _name.c_str() , i+1 , _chain->GetEntries() );
      
      Hist( "ChiSquareMass" )->Fill( eventBranches._chiMass , getStatisticsWeight() );

      //for( size_t j = 0 ; j < jetBranches._VecList.size() ; ++j ){
      //   Hist("JetPt")->Fill( jetBranches._VecList[j].Pt() , getStatisticsWeight() );
      //}
   }
   puts("Done!\n");
}


//------------------------------------------------------------------------------ 
//   Helper function implementation
//------------------------------------------------------------------------------
void SetInputTree( TTree*  tree )
{
   eventBranches.retrieveVariables( tree );
   muonBranches.retrieveVariables( tree );
   jetBranches.retrieveVariables( tree );
   elecBranches.retrieveVariables( tree );
}
