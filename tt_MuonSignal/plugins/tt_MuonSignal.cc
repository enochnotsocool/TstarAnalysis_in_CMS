/*******************************************************************************
 *
 *  Filename    : tt_MuonSignal.cc
 *  Description : Implementation for base filter class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/tt_MuonSignal/interface/tt_MuonSignal.h"
#include "TstarAnalysis/BaseClasses/interface/Selection.h"
#include "TstarAnalysis/BaseClasses/interface/Limits.h"
#include "TLorentzVector.h"
#include <iostream>

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
tt_MuonSignal::tt_MuonSignal( const edm::ParameterSet& iConfig ):
   MiniAODFilter( iConfig )
{
   eleLooseIdMapToken_   = consumes<edm::ValueMap<bool>> (iConfig.getParameter<edm::InputTag>( "eleLooseIdMap"   )) ;
   eleMediumIdMapToken_  = consumes<edm::ValueMap<bool>> (iConfig.getParameter<edm::InputTag>( "eleMediumIdMap"  )) ;
   _debug                = iConfig.getUntrackedParameter<int>  ( "Debug" , 0 );
   _jetPt                = iConfig.getUntrackedParameter<int>( "JetPt" , 30. );
   _jetNumber            = iConfig.getUntrackedParameter<int>  ( "JetNumber" , 4 );

   _selcMuonCount = fs->make<TH1F>( "MuonSelectionCount"  , "SelectionCount" , 10 , 0 , 10 );
   _selcElecCount = fs->make<TH1F>( "ElecSelectionCount"  , "SelectionCount" , 10 , 0 , 10 );
   _selcJetCount  = fs->make<TH1F>( "JetSelectionCount"   , "SelectionCount" , 10 , 0 , 10 );
   _vetoMuonCount = fs->make<TH1F>( "vetoMuonCount"       , "SelectionCount" , 10 , 0 , 10 );
   _vetoElecCount = fs->make<TH1F>( "vetoElecCount"       , "SelectionCount" , 10 , 0 , 10 );
   
   _acceptTriggers.push_back( "HLT_IsoMu27_v1" ); // MC_reminiAOD
   _acceptTriggers.push_back( "HLT_IsoMu27_v2" ); // Data
   _acceptTriggers.push_back( "HLT_IsoMu27_v3" ); // Data
}

tt_MuonSignal::~tt_MuonSignal(){}

void tt_MuonSignal::beginJob() {}
void tt_MuonSignal::endJob(){}

//------------------------------------------------------------------------------ 
//   Processing particle collection to storages classes
//------------------------------------------------------------------------------
void tt_MuonSignal::processVertex(const edm::Event& , const edm::EventSetup& )
{ 
   bool gotPV = false;
   auto vertex = _vertexList->begin() ;
   for( ; vertex != _vertexList->end() ; ++vertex ){
      if( !gotPV && isGoodPrimaryVertex( *vertex, 0 ) ){
         _primaryVertex = *vertex ;
         gotPV = true;
         break;
      }
   }
}

void tt_MuonSignal::processMuon(const edm::Event& , const edm::EventSetup& )
{
   bool selcMuon, vetoMuon;
   auto muon = _muonList->begin() ;

   _selectedMuonList.clear();
   _vetoMuonList.clear();

   for( ; muon != _muonList->end() ; ++muon ){
      selcMuon = isSelectionMuon( *muon , _primaryVertex , _selcMuonCount );
      vetoMuon = isVetoMuon( *muon , _vetoMuonCount  );
      if( selcMuon ){
         _selectedMuonList.push_back( &*muon );
      } else if( vetoMuon ) {
         _vetoMuonList.push_back( &*muon );
      } 
   }
}

void tt_MuonSignal::processElectron(const edm::Event& iEvent, const edm::EventSetup& )
{
   bool selcElec, vetoElec;

   iEvent.getByToken( eleLooseIdMapToken_   , loose_id_decisions  ) ;
   iEvent.getByToken( eleMediumIdMapToken_  , medium_id_decisions ) ;
   _selectedElectronList.clear();
   _vetoElectronList.clear();

   auto elec = _electronList->begin() ; 
   for( size_t i = 0 ; i < _electronList->size() ; ++i, ++elec ){
      auto elecPtr = _electronList->ptrAt(i);
      selcElec = isSelectionElectron( elecPtr , (*medium_id_decisions) , _selcElecCount );
      vetoElec = isVetoElectron( elecPtr , (*loose_id_decisions) , _vetoElecCount );
      if( selcElec ){
         _selectedElectronList.push_back( &*elec );
      } else if( vetoElec ){
         _vetoElectronList.push_back( &*elec );
      }
   }
}
void tt_MuonSignal::processJet(const edm::Event& , const edm::EventSetup& )
{
   bool selcJet ; 
   auto jet = _jetList->begin();

   _selectedJetList.clear();
   _selectedBJetList.clear();

   for( ; jet != _jetList->end() ; ++jet ){
      selcJet = MySelectionJet( *jet , _selcJetCount );
      if( selcJet ){
         _selectedJetList.push_back( &*jet );
         if( jet->bDiscriminator( "pfCombinedSecondaryVertexV2BJetTags" ) > 0.89 ){
            _selectedBJetList.push_back( &*jet );
         }
      }
   }
}

bool tt_MuonSignal::MySelectionJet( const pat::Jet& jet, TH1F* hist )
{
   if( hist!=NULL ) { hist->Fill(0); }
   if( jet.pt() < _jetPt ) { return false; }
   if( hist!=NULL ) { hist->Fill(1); }
   if( abs( jet.eta() ) > SELECTED_JET_ETA_LIM ) { return false; }

   //----- Loose Jet ID  ------------------------------------------------------------------------------
   if( hist!=NULL ) { hist->Fill(2); }
   if( jet.neutralHadronEnergyFraction() > 0.99 ) { return false; }
   if( jet.neutralEmEnergyFraction()     > 0.99 ) { return false; }
   if( jet.numberOfDaughters() <=1 ) { return false; }
   if( abs( jet.eta() )  < 2.4 ){
      if( jet.chargedHadronEnergyFraction() <=0 ) { return false; }
      if( jet.chargedMultiplicity() <=0         ) { return false; }
      if( jet.chargedEmEnergyFraction() > 0.99  ) { return false; }
   }

   //----- Cleaning against selected leptons  ---------------------------------------------------------
   if( hist!=NULL ) { hist->Fill(3); }
   TLorentzVector jetVec( jet.px() , jet.py() , jet.pz() , jet.energy() );
   for( const auto& el : _selectedElectronList ){
      TLorentzVector elecVec( el->px() , el->py() , el->pz() , el->energy() );
      if( elecVec.DeltaR( jetVec ) < JET_LEPTON_DELTA_R_LIM ) { return false; }
   }
   for( const auto& mu : _selectedMuonList ){
      TLorentzVector muVec( mu->px() , mu->py() , mu->pz() , mu->energy() ) ;
      if( muVec.DeltaR( jetVec ) < JET_LEPTON_DELTA_R_LIM ) { return false; }  
   } 
   if( hist!=NULL ) { hist->Fill(4); }
   return true;
}

bool tt_MuonSignal::passTrigger( const edm::Event& iEvent, const edm::EventSetup& )
{
   static unsigned int triggerindex = 0 ;
   if( ! _triggerResults.isValid() ) {
      if( _debug ){ std::cerr << "Handle is invalid!" << std::endl; }
      return false; }
   const edm::TriggerNames& triggerNames = iEvent.triggerNames( *_triggerResults );

   for( const auto& trigger : _acceptTriggers ){
      triggerindex = triggerNames.triggerIndex( trigger );
      if( _debug ) { std::cerr << "Getting trigger: " << trigger << " at " << triggerindex << std::endl; }
      if( triggerindex == triggerNames.size()  ){ 
         if( _debug ) { std::cerr << "Trigger not found" << std::endl; }
         continue ; }
      if( ! _triggerResults->wasrun( triggerindex ) ) { 
         if( _debug ){ std::cerr << "Trigger was not run" << std::endl;}
         continue; }
      if( ! _triggerResults->accept( triggerindex ) ) { 
         if( _debug ) { std::cerr << "Trigger was not accepted" << std::endl;}
         continue; }
      if( _triggerResults->error( triggerindex ) ) { 
         if( _debug ) { std::cerr << "Trigger has error " << std::endl; }
         continue; }
      return true;
   }
   return false;
}

//------------------------------------------------------------------------------ 
//   Selection Criteria requires over loading
//------------------------------------------------------------------------------
#define fillHist \
   _eventSelectionCount->Fill(i) ; ++i ;
bool tt_MuonSignal::passEventSelection( const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   unsigned int i = 0 ; 
   fillHist;
   if( !passTrigger( iEvent, iSetup ) ) { return false; }
   fillHist;
   if( _selectedMuonList.size() != 1 ){ return false; }
   fillHist ; 
   if( ! _selectedElectronList.empty() ){ return false; }
   fillHist ;
   if( ! _vetoMuonList.empty() ) { return false; }
   fillHist ; 
   if( ! _vetoElectronList.empty() ) { return false; }
   fillHist ; 
   if( _selectedJetList.size() < _jetNumber ) { return false; }
   fillHist ; 
   if( _selectedBJetList.empty() ) { return false; }
   fillHist ;
   return true; 
}


DEFINE_FWK_MODULE( tt_MuonSignal );

