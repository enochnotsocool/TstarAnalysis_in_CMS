/*******************************************************************************
 *
 *  Filename    : ggChannel_AddInfo.cc
 *  Description : Inserting information into the TTree
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  Details     :
 *
*******************************************************************************/

#include "TstarAnalysis/ggChannelAnalyzer/interface/ggChannelAnalyzer.h"

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

void ggChannelAnalyzer::FillTree( const edm::Event& iEvent )
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

void ggChannelAnalyzer::addEventInfo( const edm::Event& iEvent )
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
      _eventBranches._MET = _eventBranches._METPhi = 0 ;
   }
}

static TLorentzVector temp;
void ggChannelAnalyzer::addJet( const pat::Jet* jet )
{
   temp.SetPtEtaPhiE( jet->pt() , jet->eta() , jet->phi() , jet->energy() );
   _jetBranches._VecList.push_back( temp );
}

void ggChannelAnalyzer::addMuon( const pat::Muon* muon )
{
   temp.SetPtEtaPhiE( muon->pt() , muon->eta() , muon->phi() , muon->energy() );
   _muonBranches._VecList.push_back( temp );
   _muonBranches._trackRelIsoList.push_back( muon->trackIso()/muon->pt() );
}

void ggChannelAnalyzer::addElec( const reco::GsfElectron* elec )
{
   temp.SetPtEtaPhiE( elec->pt() , elec->eta() , elec->phi() , elec->energy() );
   _elecBranches._VecList.push_back( temp ); 
   
}

