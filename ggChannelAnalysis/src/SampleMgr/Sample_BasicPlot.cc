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
static std::vector<float>*  muonPtPtr;
static std::vector<float>*  jetPtPtr;
static std::vector<float>   muonPt;
static std::vector<float>   jetPt;

void SetInputTree( TTree* );

void SampleInfo::makeBasicPlots()
{
   printf( "Making basic plots for %s\n", _name.c_str() );
  
   //SetInputTree( _chain );
   _chain->SetBranchAddress( "ChiSqMass" , &chiMass );
   _chain->SetBranchAddress( "JetPt"     , &jetPtPtr   );
   _chain->SetBranchAddress( "MuonPt"    , &muonPtPtr  );

   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      _chain->GetEntry(i);
      jetPt = *(jetPtPtr);
      muonPt = *(muonPtPtr);

      printf( "\r[%s] Event %lld/%lld.... " , _name.c_str() , i+1 , _chain->GetEntries() );
      
      Hist( "ChiSquareMass" )->Fill( chiMass );

      for( size_t j = 0 ; j < jetPt.size() ; ++j ){
         Hist("JetPt")->Fill( jetPt[j] );
         Hist("BJetPt")->Fill( jetPt[j] );
      }
      for( size_t j = 0 ; j < muonPt.size(); ++j ){
         Hist("LeptonPt")->Fill( muonPt[j] );
      }

      for( size_t j = 6 ; j <= jetPt.size() ; ++j ){
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
