/*******************************************************************************
 *
 *  Filename    : BaseAnalyzer_addVariables.cc
 *  Description : Ntuplizing process
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/BaseClasses/interface/BaseAnalyzer.h"

//----- Muon Information  ------------------------------------------------------
void BaseAnalyzer::addMuonVariables()
{
   _muonBranches.clear(); // Clearing previous event contents
   for( const auto& muon : _selectedMuonList ){
      _muonBranches.Pt.push_back( muon->pt() );
      _muonBranches.Eta.push_back( muon->eta() );
      _muonBranches.Phi.push_back( muon->phi() );
      _muonBranches.Energy.push_back( muon->energy() );
      _muonBranches.trackRelIso.push_back( muon->trackIso() / muon->pt() );
   }
}

//----- Jet Information  -------------------------------------------------------
void addJet( MiniJetBranches&  b , const pat::Jet* j )
{
   b.Pt.push_back( j->pt() );
   b.Eta.push_back( j->eta() );
   b.Phi.push_back( j->phi() );
   b.Energy.push_back( j->energy() );    
}

void BaseAnalyzer::addJetVariables()
{
   _jetBranches.clear();
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
   _elecBranches.clear();
   for( const auto elec : _selectedElectronList ){
      _elecBranches.Pt.push_back( elec->pt() );
      _elecBranches.Eta.push_back( elec->eta() );
      _elecBranches.Phi.push_back( elec->phi() );
      _elecBranches.Energy.push_back( elec->energy() );
   }
}

void BaseAnalyzer::addEventVariables( const edm::Event& iEvent )
{
   //printf("Getting run info...\n" );
   _eventBranches._RunNumber           = iEvent.id().run();
   _eventBranches._EventNumber         = iEvent.id().event();
   _eventBranches._BunchCrossingNumber = iEvent.bunchCrossing();
   _eventBranches._LumiNumber          = iEvent.luminosityBlock();

   //printf("Getting Object Info...\n");
   _eventBranches._MuonCount     = _selectedMuonList.size();
   _eventBranches._ElectronCount = _selectedElectronList.size();
   _eventBranches._JetCount      = _selectedBJetList.size() + _selectedLJetList.size();
   _eventBranches._VertexCount   = _vertexList->size();

   //printf("Getting PileUp Info\n");
   if( !iEvent.isRealData() ){
      _eventBranches._pileUp = (unsigned int)_pileupList->begin()->getTrueNumInteractions() ;
   } else {
      _eventBranches._pileUp = 1.0 ; 
   }

   // printf("Getting METInfo\n");
   if( _metList.isValid() ){
      _eventBranches._MET    = _metList->begin()->pt();
      _eventBranches._METPhi = _metList->begin()->phi();
   } else {
     //  std::cout << "Bad MET" << std::endl;
      _eventBranches._MET = _eventBranches._METPhi = 0 ;
   }

}

//------------------------------------------------------------------------------ 
//   Virtual function to be overloaded
//------------------------------------------------------------------------------
void BaseAnalyzer::addCustomVariables(const edm::Event&){}
