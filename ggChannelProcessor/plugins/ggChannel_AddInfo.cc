/*******************************************************************************
 *
 *  Filename    : ggChannel_AddInfo.cc
 *  Description : Inserting information into the TTree
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  Details     :
 *
*******************************************************************************/

#include "TstarAnalysis/ggChannelProcessor/interface/ggChannelProcessor.h"

static float pileUpWeight[120] = {
   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 
   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 
   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
   1.00, 1.00, 1.00
};

void ggChannelProcessor::FillTree( const edm::Event& iEvent )
{
   _jetBranches.clear();
   _elecBranches.clear();
   _muonBranches.clear();

   addEventInfo( iEvent );
   for( const auto& muon : _selectedMuonList ){ addMuon( muon ); }
   for( const auto& elec : _selectedElecList ){ addElec( elec ); }
   for( const auto& jet  : _selectedBJetList ){ addJet( jet ); } 
   for( const auto& jet  : _selectedLJetList ){ addJet( jet ); }
   _tree->Fill();
}

void ggChannelProcessor::addEventInfo( const edm::Event& iEvent )
{
   _eventBranches._RunNumber           = iEvent.id().run();
   _eventBranches._EventNumber         = iEvent.id().event();
   _eventBranches._BunchCrossingNumber = iEvent.bunchCrossing();
   _eventBranches._LumiNumber          = iEvent.luminosityBlock();

   _eventBranches._MuonCount     = _selectedMuonList.size();
   _eventBranches._ElectronCount = _selectedElecList.size();
   _eventBranches._JetCount      = _selectedBJetList.size() + _selectedLJetList.size();

   _eventBranches._VertexCount = _rawVertexList->size();
   _eventBranches._chiMass     = computeChiSqMass(); 

   if( !iEvent.isRealData() ){
      _eventBranches._pileUpWeight = pileUpWeight[ (unsigned int)_rawPileupList->begin()->getTrueNumInteractions() ] ;
   } else {
      _eventBranches._pileUpWeight = 1.0 ; 
   }
   if( _rawMETList.isValid() ){
      _eventBranches._MET    = _rawMETList->begin()->pt();
      _eventBranches._METPhi = _rawMETList->begin()->phi();
   } else {
      std::cout << "Bad MET" << std::endl;
      _eventBranches._MET = _eventBranches._METPhi = 0 ;
   }

   for( const auto& muon : _selectedMuonList ){ addMuon( muon ); }
   for( const auto& elec : _selectedElecList ){ addElec( elec ); }
   for( const auto& jet  : _selectedBJetList ){ addJet( jet ); }
   for( const auto& jet  : _selectedLJetList ){ addJet( jet ); }
}

static TLorentzVector temp;
void ggChannelProcessor::addJet( const pat::Jet* jet )
{
   _jetBranches._PtList.push_back( jet->pt() );
   _jetBranches._EtaList.push_back( jet->eta() );
   _jetBranches._PhiList.push_back( jet->phi() );
   _jetBranches._EnergyList.push_back( jet->energy() );
}

void ggChannelProcessor::addMuon( const pat::Muon* muon )
{
   _muonBranches._PtList.push_back( muon->pt() );
   _muonBranches._EtaList.push_back( muon->eta() );
   _muonBranches._PhiList.push_back( muon->phi() );
   _muonBranches._EnergyList.push_back( muon->energy() );
   _muonBranches._trackRelIsoList.push_back( muon->trackIso()/muon->pt() );
}

void ggChannelProcessor::addElec( const reco::GsfElectron* elec )
{
   _elecBranches._PtList.push_back( elec->pt() );
   _elecBranches._EtaList.push_back( elec->eta() );
   _elecBranches._PhiList.push_back( elec->phi() );
   _elecBranches._EnergyList.push_back( elec->energy() );
}

