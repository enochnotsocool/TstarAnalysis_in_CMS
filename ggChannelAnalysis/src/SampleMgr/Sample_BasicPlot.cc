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
//   Helper variables
//------------------------------------------------------------------------------
static MiniEventBranches    eventBranches;
static MiniJetBranches      jetBranches;
static MiniMuonBranches     muonBranches;
static MiniElectronBranches elecBranches;
static float chiMass ;

void SetInputTree( TTree* );

void SampleMgr::makeBasicPlots()
{
   printf( "Making basic plots for %s\n", _name.c_str() );
  
   SetInputTree( _chain );
   _chain->SetBranchAddress( "ChiSqMass" , &chiMass );

   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      printf( "\r[%s] Event %lld/%lld.... " , _name.c_str() , i+1 , _chain->GetEntries() );
      _chain->GetEntry(i);
      const auto& jetPt  = *(jetBranches.PtPtr);
      const auto& jetEta = *(jetBranches.EtaPtr);
      const auto& muonPt = *(muonBranches.PtPtr);
      const auto& muonEta= *(muonBranches.EtaPtr);
      const auto& elecPt = *(elecBranches.PtPtr);
      const auto& elecEta= *(elecBranches.EtaPtr);
      
      Hist( "ChiSquareMass" )->Fill( chiMass );
      Hist( "MET" )->Fill( eventBranches._MET );
      Hist( "JetCount" )->Fill( eventBranches._JetCount );

      for( size_t j = 0 ; j < jetPt.size() ; ++j ){
         Hist("JetPt")->Fill( jetPt[j] );
         Hist("JetEta")->Fill( jetEta[j] );
      }
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

float SampleMgr::getWeightedEventCount() const 
{
   float ans;
   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      ans += 1; // Should be event way event weight;
   }
   return ans; 
}

float SampleMgr::getExpectedYield( float totalLumi ) const {
   return totalLumi * _cross_section * _selection_eff ; }

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
