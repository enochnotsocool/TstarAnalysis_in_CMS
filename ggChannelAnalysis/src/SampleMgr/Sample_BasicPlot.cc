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
static std::string plotname;

void SetInputTree( TTree* );

void SampleInfo::makeBasicPlots()
{
   printf( "Making basic plots for %s\n", _name.c_str() );
  
   SetInputTree( _chain );
   _chain->SetBranchAddress( "ChiSqMass" , &chiMass );
   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      _chain->GetEntry(i);
      printf( "\r[%s] Event %lld/%lld.... " , _name.c_str() , i+1 , _chain->GetEntries() );
      
      Hist( "ChiSquareMass" )->Fill( chiMass );

      //for( size_t j = 0 ; j < jetBranches._PtList.size() ; ++j ){
      //   Hist("JetPt")->Fill( jetBranches._PtList[j] );
      //   Hist("BJetPt")->Fill( jetBranches._PtList[j] );
      //}
      for( size_t j = 0 ; j < muonBranches._PtList.size(); ++j ){
         Hist("LeptonPt")->Fill( muonBranches._PtList[j] );
      }

      for( size_t j = 6 ; j <= jetBranches._PtList.size() ; ++j ){
         Hist("JetCount")->Fill(i);
      }
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
