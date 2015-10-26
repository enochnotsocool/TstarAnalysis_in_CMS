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
      _muonBranches._PtList.push_back( muon->pt() );
      _muonBranches._EtaList.push_back( muon->eta() );
      _muonBranches._PhiList.push_back( muon->phi() );
      _muonBranches._EnergyList.push_back( muon->energy() );
      _muonBranches._trackRelIsoList.push_back( muon->trackIso() / muon->pt() );
   }
}

//----- Jet Information  -------------------------------------------------------
void addJet( MiniJetBranches&  b , const pat::Jet* j )
{
   b._PtList.push_back( j->pt() );
   b._EtaList.push_back( j->eta() );
   b._PhiList.push_back( j->phi() );
   b._EnergyList.push_back( j->energy() );    
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
      _elecBranches._PtList.push_back( elec->pt() );
      _elecBranches._EtaList.push_back( elec->eta() );
      _elecBranches._PhiList.push_back( elec->phi() );
      _elecBranches._EnergyList.push_back( elec->energy() );
   }
}

void BaseAnalyzer::addEventVariables( const edm::Event& iEvent )
{
   printf("Getting run info...\n" );
   _eventBranches._RunNumber           = iEvent.id().run();
   _eventBranches._EventNumber         = iEvent.id().event();
   _eventBranches._BunchCrossingNumber = iEvent.bunchCrossing();
   _eventBranches._LumiNumber          = iEvent.luminosityBlock();

   printf("Getting Object Info...\n");
   _eventBranches._MuonCount     = _selectedMuonList.size();
   _eventBranches._ElectronCount = _selectedElectronList.size();
   _eventBranches._JetCount      = _selectedBJetList.size() + _selectedLJetList.size();
   _eventBranches._VertexCount = _vertexList->size();

   printf("Getting PileUp Info\n");
   if( !iEvent.isRealData() ){
      _eventBranches._pileUp = (unsigned int)_pileupList->begin()->getTrueNumInteractions() ;
   } else {
      _eventBranches._pileUp = 1.0 ; 
   }

   printf("Getting METInfo\n");
   if( _metList.isValid() ){
      _eventBranches._MET    = _metList->begin()->pt();
      _eventBranches._METPhi = _metList->begin()->phi();
   } else {
      std::cout << "Bad MET" << std::endl;
      _eventBranches._MET = _eventBranches._METPhi = 0 ;
   }

}

//------------------------------------------------------------------------------ 
//   Virtual function to be overloaded
//------------------------------------------------------------------------------
void BaseAnalyzer::addCustomVariables(const edm::Event&){}
