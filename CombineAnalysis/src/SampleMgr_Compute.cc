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
   float eventWeight ;
   bool  updateEventWeightCount = (_eventWeightCount == 0.0 );
   printf( "Making basic plots for %s\n", Stringify(_name).c_str() );

   printf( "Sanity check for _histMap...\n" );
   for( const auto& pair : _histMap ){
      printf("%s %p\n" , Stringify(pair.first).c_str() , pair.second );
   }

   for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
      _chain->GetEntry(i);
      
      printf( "[%s] Event [%6lld/%6lld]: ....\r" , Stringify(_name).c_str() , i+1 , _chain->GetEntries() );

      eventWeight = _event->TotalEventWeight();
      if( updateEventWeightCount ){
         _eventWeightCount+= eventWeight; } 

      //----- Kinematic plots  -------------------------------------------------------
      Hist( MET )->Fill( _event->MET() , eventWeight  );
      Hist( JetCount )->Fill( _event->JetList().size() , eventWeight );
      // Hist( VertexCount )->Fill( eventBranches.VertexCount , eventWeight );

      Hist( JetPt )->Fill( _event->JetList()[0].pt() , eventWeight );
      Hist( JetEta )->Fill( _event->JetList()[0].eta() , eventWeight );

      for( const auto& mu : _event->MuonList() ){
         Hist(LeptonPt)->Fill( mu.pt() , eventWeight  );
         Hist(LeptonEta)->Fill( mu.eta() , eventWeight );
      }
      for( const auto& el : _event->ElectronList() ){
         Hist(LeptonPt)->Fill( el.pt() , eventWeight );
         Hist(LeptonEta)->Fill( el.eta() ,eventWeight );
      }

      //----- Signal variable plots  -------------------------------------------------
      Hist( ChiSquareTstarMass )->Fill( _chisq->TstarMass() , eventWeight );
      Hist( ChiSquareTMass )->Fill( _chisq->LeptonicTop().Mag() , eventWeight );
      Hist( HitFitTstarMass )->Fill( _hitfit->TstarMass() , eventWeight );
      Hist( HitFitTMass )->Fill( _hitfit->LeptonicTop().Mag() , eventWeight );
   }
   puts("Done!\n");
}

float SampleMgr::getRawEventCount() const {
   if( _rawEventsCount == 0.0 ) {
      _rawEventsCount = _chain->GetEntries();
   }
   return _rawEventsCount;
}

float SampleMgr::getEventWeightedCount() const 
{
   if( _eventWeightCount == 0.0 ){ 
      for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
         _chain->GetEntry(i);
         _eventWeightCount += _event->TotalEventWeight();
      }
   }
   return _eventWeightCount; 
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

