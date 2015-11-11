/*******************************************************************************
 *
 *  Filename    : BaseFilter.cc
 *  Description : Implementation for base filter class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/BaseClasses/interface/BaseFilter.h"
#include "TstarAnalysis/BaseClasses/interface/Selection.h"
#include <iostream>

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
BaseFilter::BaseFilter( const edm::ParameterSet& iConfig ):
   MiniAODFilter( iConfig )
{
   eleLooseIdMapToken_   = consumes<edm::ValueMap<bool>> (iConfig.getParameter<edm::InputTag>( "eleLooseIdMap"   )) ;
   eleMediumIdMapToken_  = consumes<edm::ValueMap<bool>> (iConfig.getParameter<edm::InputTag>( "eleMediumIdMap"  )) ;
   _debug                = iConfig.getUntrackedParameter<int>( "Debug" , 0 );

   _selcMuonCount = fs->make<TH1F>( "MuonSelectionCount"  , "SelectionCount" , 10 , 0 , 10 );
   _selcElecCount = fs->make<TH1F>( "ElecSelectionCount"  , "SelectionCount" , 10 , 0 , 10 );
   _selcJetCount  = fs->make<TH1F>( "JetSelectionCount"   , "SelectionCount" , 10 , 0 , 10 );
   _vetoMuonCount = fs->make<TH1F>( "vetoMuonCount"       , "SelectionCount" , 10 , 0 , 10 );
   _vetoElecCount = fs->make<TH1F>( "vetoElecCount"       , "SelectionCount" , 10 , 0 , 10 );
}

BaseFilter::~BaseFilter(){}

void BaseFilter::beginJob() {}
void BaseFilter::endJob(){}

//------------------------------------------------------------------------------ 
//   Processing particle collection to storages classes
//------------------------------------------------------------------------------
void BaseFilter::processVertex(const edm::Event& , const edm::EventSetup& )
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

void BaseFilter::processMuon(const edm::Event& , const edm::EventSetup& )
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

void BaseFilter::processElectron(const edm::Event& iEvent, const edm::EventSetup& )
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
void BaseFilter::processJet(const edm::Event& , const edm::EventSetup& )
{
   bool selcJet ; 
   auto jet = _jetList->begin();

   _selectedJetList.clear();
   _selectedBJetList.clear();

   for( ; jet != _jetList->end() ; ++jet ){
      selcJet = isSelectionJet( *jet , _selectedMuonList , _selectedElectronList , _selcJetCount );
      if( selcJet ){
         _selectedJetList.push_back( &*jet );
         if( jet->bDiscriminator( "pfCombinedSecondaryVertexV2BJetTags" ) > 0.89 ){
            _selectedBJetList.push_back( &*jet );
         }
      }
   }
}

bool BaseFilter::passTrigger( const edm::Event& iEvent, const edm::EventSetup& )
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
bool BaseFilter::passEventSelection( const edm::Event&, const edm::EventSetup& )
{ return true; }


DEFINE_FWK_MODULE( BaseFilter );

