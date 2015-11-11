/*******************************************************************************
 *
 *  Filename    : Sample_BasicPlot.cc
 *  Description : Implementation of basic plots 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "SampleMgr.h"
#include "MiniEventBranches.h"
#include "MiniJetBranches.h"
#include "MiniMuonBranches.h"
#include "MiniElectronBranches.h"

//------------------------------------------------------------------------------ 
//   Helper variables and functions
//------------------------------------------------------------------------------
static MiniEventBranches    eventBranches;
static MiniJetBranches      jetBranches;
static MiniMuonBranches     muonBranches;
static MiniElectronBranches elecBranches;
void SetInputTree( TTree* );

//------------------------------------------------------------------------------ 
//   SampleMgr method implementation
//------------------------------------------------------------------------------
void SampleMgr::makeBasicPlots()
{
   float eventWeight ;
   float totalWeight ;
   const float sampleWeight = _sample_weight; 
   printf( "Making basic plots for %s\n", _name.c_str() );
  
   SetInputTree( _chain );

   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      printf( "\r[%s] Event %lld/%lld.... " , _name.c_str() , i+1 , _chain->GetEntries() );
      _chain->GetEntry(i);

      eventWeight = eventBranches._eventWeight;
      totalWeight = sampleWeight * eventWeight;

      const auto& jetPt  = *(jetBranches.PtPtr);
      const auto& jetEta = *(jetBranches.EtaPtr);
      const auto& muonPt = *(muonBranches.PtPtr);
      const auto& muonEta= *(muonBranches.EtaPtr);
      const auto& elecPt = *(elecBranches.PtPtr);
      const auto& elecEta= *(elecBranches.EtaPtr);
      
      Hist( "ChiSquareMass" )->Fill( eventBranches._chiSqMass );
      Hist( "MET" )->Fill( eventBranches._MET );
      Hist( "JetCount" )->Fill( eventBranches._JetCount );
      Hist( "VertexCountNoWeight" )->Fill( eventBranches._VertexCount , sampleWeight );
      Hist( "VertexCount" )->Fill( eventBranches._VertexCount , totalWeight );


      Hist("JetPt")->Fill( jetPt[0] );
      Hist("JetEta")->Fill( jetEta[0] );

      for( size_t j = 0 ; j < muonPt.size(); ++j ){
         Hist("LeptonPt")->Fill( muonPt[j] );
         Hist("LeptonEta")->Fill( muonEta[j] );
      }
      for( size_t j = 0 ; j < elecPt.size() ; ++j ){
         Hist("LeptonPt")->Fill( elecPt[j] );
         Hist("LeptonEta")->Fill( elecEta[j] );
      }
   }
   puts("Done!\n");
}

float SampleMgr::getRawEventCount() const {
   return _chain->GetEntries();
}

float SampleMgr::getEventWeightedCount() const 
{
   float ans = 0;
   SetInputTree( _chain );
   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      _chain->GetEntry(i);
      ans += eventBranches._eventWeight;
   }
   return ans; 
}

float SampleMgr::getAverageEventWeight() const 
{
   return getEventWeightedCount() / getRawEventCount(); 
}

float SampleMgr::getTotalWeightedCount() const 
{
   return getEventWeightedCount() * _sample_weight ; 
}

float SampleMgr::getAverageTotalWeight() const 
{
   return getTotalWeightedCount() / getRawEventCount();
}

float SampleMgr::getExpectedYield( float totalLumi ) const {
   return totalLumi * _cross_section * _selection_eff * getAverageTotalWeight() ;
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