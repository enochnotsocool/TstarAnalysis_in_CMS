/*******************************************************************************
 *
 *  Filename    : Sample_BasicPlot.cc
 *  Description : Implementation of basic plots 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/SampleMgr.h"

#include "TstarAnalysis/RootFormat/interface/MiniEvent.h"
#include "TstarAnalysis/RootFormat/interface/MiniMuon.h"
#include "TstarAnalysis/RootFormat/interface/MiniJet.h"
#include "TstarAnalysis/RootFormat/interface/MiniElectron.h"
#include "TstarAnalysis/RootFormat/interface/ChiSquareResult.h"
#include "TstarAnalysis/RootFormat/interface/HitFitResult.h"

//------------------------------------------------------------------------------ 
//   SampleMgr method implementation
//------------------------------------------------------------------------------
void SampleMgr::makeBasicPlots()
{
   MiniEvent*        event;
   ChiSquareResult*  chiResult;
   HitFitResult*     hitfitResult;
   float eventWeight ;

   _chain->SetBranchAddress( "MiniEvent" , &event );
   _chain->SetBranchAddress( "ChiSquareResult" , &chiResult );
   _chain->SetBranchAddress( "HitFitResult" , &hitfitResult );

   printf( "Making basic plots for %s\n", Stringify(_name).c_str() );
  
   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      printf( "\r[%s] Event %lld/%lld.... " , Stringify(_name).c_str() , i+1 , _chain->GetEntries() );
      _chain->GetEntry(i);

      eventWeight = event->TotalEventWeight();
      
      Hist( ChiSquareMass )->Fill( chiResult->TstarMass() , eventWeight );
      Hist( MET )->Fill( event->MET() , eventWeight  );
      // Hist( JetCount )->Fill( jetBranches.Size , eventWeight );
      // Hist( VertexCount )->Fill( eventBranches.VertexCount , eventWeight );


      Hist( JetPt )->Fill( event->JetList()[0].pt() , eventWeight );
      Hist( JetEta )->Fill( event->JetList()[0].eta() , eventWeight );

      for( const auto& mu : event->MuonList() ){
         Hist(LeptonPt)->Fill( mu.pt() , eventWeight  );
         Hist(LeptonEta)->Fill( mu.eta() , eventWeight );
      }
      for( const auto& el : event->ElectronList() ){
         Hist(LeptonPt)->Fill( el.pt() , eventWeight );
         Hist(LeptonEta)->Fill( el.eta() ,eventWeight );
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
   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      _chain->GetEntry(i);
      ans += 1;
      // ans += eventBranches._eventWeight;
   }
   return ans; 
}

float SampleMgr::getAverageEventWeight() const 
{
   return getEventWeightedCount() / getRawEventCount(); 
}

float SampleMgr::getTotalWeightedCount() const 
{
   return getEventWeightedCount() * _sample_weight.CentralValue(); ; 
}

float SampleMgr::getAverageTotalWeight() const 
{
   if( getRawEventCount() == 0 ) return 0;
   return getTotalWeightedCount() / getRawEventCount();
}

Parameter SampleMgr::getExpectedYield( float totalLumi ) const {
   return totalLumi * _cross_section * _selection_eff * getAverageTotalWeight() ;
}

