/*******************************************************************************
 *
 *  Filename    : BaseAnalyzer_addVariables.cc
 *  Description : Ntuplizing process
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/BaseClasses/interface/BaseAnalyzer.h"
#include <iostream>
using namespace std;

//----- Muon Information  ------------------------------------------------------
void BaseAnalyzer::addMuon()
{
   MiniMuon temp; 
   if( _debug ) { cerr << "Adding Muon Information" << endl; }
   for( const auto& muon : _selectedMuonList ){
      temp.MakeMiniMuon( *muon  );
      _event->AddMuon( temp );
   }
}

//----- Getting Jet Information  -----------------------------------------------
void BaseAnalyzer::addJet()
{
   MiniJet temp;
   for( const auto& jet: _selectedBJetList ){
      temp.MakeMiniJet( *jet );
      _event->AddJet( temp );
   }
   for( const auto& jet: _selectedLJetList ){
      temp.MakeMiniJet( *jet );
      _event->AddJet( temp ); 
   }
}

//----- Electron Information  --------------------------------------------------
void BaseAnalyzer::addElectron()
{
   MiniElectron temp;
   for( const auto& el: _selectedElectronList ){
      temp.MakeMiniElectron( *el );
      _event->AddElectron( temp );
   }
}

void BaseAnalyzer::addEventVariables( const edm::Event& iEvent )
{
   if( _debug ) { cerr << "Getting Run Information" << endl; }
   _event->SetRunNumber( iEvent.id().run() );
   _event->SetEventNumber( iEvent.id().event() );
   _event->SetBunchCrossing( iEvent.bunchCrossing() );
   _event->SetLumiNumber( iEvent.luminosityBlock() );

   if( _debug ) { cerr << "Getting MET information" << endl; }
   if( _metList.isValid() ){
      _event->SetMet( _metList->begin()->pt(), _metList->begin()->phi() );
   } else {
      std::cout << "Bad MET" << std::endl;
      _event->SetMet( 0, 0 ) ;
   }
   
   if( _debug ) { cerr << "Getting PileUp information" << endl; }
   if( !iEvent.isRealData() ){
      _event->SetPileUp( _pileupList->begin()->getTrueNumInteractions() );
   } else {
      _event->SetPileUp( 0 );
   }

}

//------------------------------------------------------------------------------ 
//   Virtual function to be overloaded
//------------------------------------------------------------------------------
void BaseAnalyzer::addCustomVariables(const edm::Event&){}
