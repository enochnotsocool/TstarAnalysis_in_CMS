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

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------ 
//   Making basic plots for the particles
//------------------------------------------------------------------------------
void SampleMgr::MakeBasicPlots()
{
   float eventWeight ;
   long long n = _chain->GetEntries();
   bool  updateEventWeightCount = (_eventWeightCount == 0.0 );

   cout << "\r[" << _name << "]: " << flush ;
   for( long long i = 0 ; i < n ; ++i ){
      _chain->GetEntry(i);
      
      cout << "\r[" << _name << "]: Running event: " << i+1 << "/" << n << "..." << flush ;

      eventWeight = _event->TotalEventWeight();
      if( updateEventWeightCount ){
         _eventWeightCount+= eventWeight; } 

      //----- Kinematic plots  -------------------------------------------------------
      Hist("MET")->Fill( _event->MET() , eventWeight  );
      Hist("JetCount")->Fill( _event->JetList().size() , eventWeight );
      // Hist( VertexCount )->Fill( eventBranches.VertexCount , eventWeight );

      Hist("JetPt")->Fill( _event->JetList()[0].pt() , eventWeight );
      Hist("JetEta")->Fill( _event->JetList()[0].eta() , eventWeight );

      for( const auto& mu : _event->MuonList() ){
         Hist("LeptonPt")->Fill( mu.pt() , eventWeight  );
         Hist("LeptonEta")->Fill( mu.eta() , eventWeight );
      }
      for( const auto& el : _event->ElectronList() ){
         Hist("LeptonPt")->Fill( el.pt() , eventWeight );
         Hist("LeptonEta")->Fill( el.eta() ,eventWeight );
      }

      //----- Signal variable plots  -------------------------------------------------
      Hist("ChiSquareTstarMass")->Fill( _event->GetChiSquare().TstarMass() , eventWeight );
      Hist("ChiSquareTMass")->Fill( _event->GetChiSquare().LeptonicTop().Mag() , eventWeight );
      Hist("HitFitTstarMass")->Fill( _event->GetHitFit().TstarMass() , eventWeight );
      Hist("HitFitTMass")->Fill( _event->GetHitFit().LeptonicTop().Mag() , eventWeight );
   }
   cout << "Done!" << endl;
}

