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
void BaseAnalyzer::addMuonVariables()
{
   if( _debug ) { cerr << "Adding Muon Information" << endl; }
   _muonBranches.Size = 0 ;
   for( const auto& muon : _selectedMuonList ){
      _muonBranches.Pt[_muonBranches.Size]= muon->pt() ;
      _muonBranches.Eta[_muonBranches.Size]= muon->eta() ;
      _muonBranches.Phi[_muonBranches.Size]= muon->phi() ;
      _muonBranches.Energy[_muonBranches.Size]= muon->energy() ;
      _muonBranches.TrackRelIso[_muonBranches.Size]= muon->trackIso() / muon->pt() ;
   }
}

//----- Jet Information  -------------------------------------------------------
void addJet( JetBranches&  b , const pat::Jet* j )
{
   b.Pt[b.Size]= j->pt();
   b.Eta[b.Size]= j->eta();
   b.Phi[b.Size]= j->phi();
   b.Energy[b.Size]= j->energy();
   b.Size++;
}

void BaseAnalyzer::addJetVariables()
{
   if( _debug ) { cerr << "Entering Jet loops Information" << endl; }
   _jetBranches.Size=0;
   for( const auto& jet : _selectedLJetList ){
      addJet( _jetBranches , jet );
   }
   for( const auto& jet : _selectedBJetList ){
      addJet( _jetBranches , jet );
   }
}

//----- Electron Information  --------------------------------------------------
void BaseAnalyzer::addElectronVariables()
{
   if( _debug ) { cerr << "Adding electron Information" << endl; }
   _elecBranches.Size=0;
   for( const auto elec : _selectedElectronList ){
      _elecBranches.Pt[_elecBranches.Size]     = elec->pt() ;
      _elecBranches.Eta[_elecBranches.Size]    = elec->eta();
      _elecBranches.Phi[_elecBranches.Size]    = elec->phi();
      _elecBranches.Energy[_elecBranches.Size] = elec->energy();
      _elecBranches.Size++;
   }
}

void BaseAnalyzer::addEventVariables( const edm::Event& iEvent )
{
   if( _debug ) { cerr << "Getting Run Information" << endl; }
   _eventBranches.RunNumber           = iEvent.id().run();
   _eventBranches.EventNumber         = iEvent.id().event();
   _eventBranches.BunchCrossingNumber = iEvent.bunchCrossing();
   _eventBranches.LumiNumber          = iEvent.luminosityBlock();

   if( _debug ) { cerr << "Getting MET information" << endl; }
   if( _metList.isValid() ){
      _eventBranches.MET    = _metList->begin()->pt();
      _eventBranches.METPhi = _metList->begin()->phi();
   } else {
     //  std::cout << "Bad MET" << std::endl;
      _eventBranches.MET = _eventBranches.METPhi = 0 ;
   }
   
   if( _debug ) { cerr << "Getting PileUp information" << endl; }
   if( !iEvent.isRealData() ){
      _eventBranches.pileUp = (unsigned int)_pileupList->begin()->getTrueNumInteractions() ;
   } else {
      _eventBranches.pileUp = 1.0 ; 
   }

   // printf("Getting METInfo\n");

}

//------------------------------------------------------------------------------ 
//   Virtual function to be overloaded
//------------------------------------------------------------------------------
void BaseAnalyzer::addCustomVariables(const edm::Event&){}
