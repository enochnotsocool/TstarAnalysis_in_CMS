/*******************************************************************************
 *
 *  Filename    : BaseAnalyzer.cc
 *  Description : Implementation for BaseAnalyzer class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#include "TstarAnalysis/BaseClasses/interface/BaseAnalyzer.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
BaseAnalyzer::BaseAnalyzer( const edm::ParameterSet& iConfig ):
   MiniAODAnalyzer(iConfig),
   _debug( iConfig.getUntrackedParameter<int>( "Debug" , 0 ) ),
   _objSel( iConfig.getParameter<edm::ParameterSet>( "ObjectSelectionParameter" ))
{
   if( _debug ){ cerr << "Spawning Instance of BaseAnalyzer" << endl; }
   eleLooseIdMapToken_   = consumes<edm::ValueMap<bool>> (iConfig.getParameter<edm::InputTag>( "eleLooseIdMap"   )) ;
   eleMediumIdMapToken_  = consumes<edm::ValueMap<bool>> (iConfig.getParameter<edm::InputTag>( "eleMediumIdMap"  )) ;

   if( _debug ){ cerr << "Generating storage tree..." << flush ; }
   _event = new MiniEvent();
   _tree = fs->make<TTree>( "TstarAnalysis" , "TstarAnalysis" );
   _tree->Branch( "MiniEvent" , "MiniEvent" , &_event , 32000 , 99 );
   if( _debug ){ cerr << "Done!" << endl; }
}

BaseAnalyzer::~BaseAnalyzer() {}

void BaseAnalyzer::beginJob() {}
void BaseAnalyzer::endJob() {}

//------------------------------------------------------------------------------ 
//   Main processing sections
//------------------------------------------------------------------------------
void BaseAnalyzer::processVertex(const edm::Event& , const edm::EventSetup& )
{ 
   for( auto vertex = _vertexList->begin() ; vertex != _vertexList->end() ; ++vertex ){
      if( _objSel.isGoodPrimaryVertex( *vertex, 0 ) ){
         _primaryVertex = *vertex ;
         break;
      }
   }
}

void BaseAnalyzer::processMuon(const edm::Event& , const edm::EventSetup& )
{
   _selectedMuonList.clear();
   for( auto muon = _muonList->begin() ; muon != _muonList->end() ; ++muon ){
      if( _objSel.isSelectionMuon( *muon , _primaryVertex ) ){
         _selectedMuonList.push_back( &*muon ); } 
   }
}

void BaseAnalyzer::processElectron(const edm::Event& iEvent, const edm::EventSetup& )
{
   iEvent.getByToken( eleMediumIdMapToken_  , medium_id_decisions ) ;
   _selectedElectronList.clear();

   auto elec = _electronList->begin() ; 
   for( size_t i = 0 ; i < _electronList->size() ; ++i, ++elec ){
      auto elecPtr = _electronList->ptrAt(i);
      if( _objSel.isSelectionElectron( elecPtr , (*medium_id_decisions) ) ) {
         _selectedElectronList.push_back( &*elec ); }
   }
}

void BaseAnalyzer::processJet(const edm::Event& , const edm::EventSetup& )
{
   _selectedLJetList.clear();
   _selectedBJetList.clear();

   for( auto jet = _jetList->begin() ; jet != _jetList->end() ; ++jet ){
      if( _objSel.isSelectionJet( *jet , _selectedMuonList , _selectedElectronList ) ){
         if( jet->bDiscriminator( "pfCombinedSecondaryVertexV2BJetTags" ) > 0.89 ){
            _selectedBJetList.push_back( &*jet );
         } else {
            _selectedLJetList.push_back( &*jet );
         }
      }
   }
}

void BaseAnalyzer::processEvent( const edm::Event& iEvent , const edm::EventSetup& )
{
   if( _debug ) { cerr << "Processing Event" << endl; }
   addEventVariables(iEvent);
   addMuon();
   addElectron();
   addJet();
   addCustomVariables(iEvent);

   _tree->Fill();
}
