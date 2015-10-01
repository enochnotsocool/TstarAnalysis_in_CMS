/*******************************************************************************
 *
 *  Filename    : ggChannelFilter.cc
 *  Description : ED Plugini setups for ggChannel Event Selection
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/GGChannelFilter/interface/ggChannelFilter.h"
#include "TstarAnalysis/Selection/interface/Selection.h"
#include <iostream>

//------------------------------------------------------------------------------ 
//   EDM plugin initializing functions
//------------------------------------------------------------------------------
ggChannelFilter::ggChannelFilter( const edm::ParameterSet& iConfig )
{
   _muonsrc   = iConfig.getParameter<edm::InputTag>( "muonsrc"   ) ;
   _elecsrc   = iConfig.getParameter<edm::InputTag>( "elecsrc"   ) ;
   _jetsrc    = iConfig.getParameter<edm::InputTag>( "jetsrc"    ) ;
   _vertexsrc = iConfig.getParameter<edm::InputTag>( "vertexsrc" ) ;
   _rhosrc    = iConfig.getParameter<edm::InputTag>( "rhosrc"  ) ;
   _beamspotsrc = iConfig.getParameter<edm::InputTag>( "beamspotsrc" );
   _convsrc   = iConfig.getParameter<edm::InputTag> ( "convsrc" );
}


ggChannelFilter::~ggChannelFilter()
{ }

void ggChannelFilter::beginStream( edm::StreamID )
{
   totalEvent = 0 ;
   passedEvent = 0;
   muonEvents = 0;
   elecEvents = 0;
   for( int i = 0 ;  i < 10 ; ++i ){
      muonCount[i] = 0;
      elecCount[i] = 0 ;
   }
}

void ggChannelFilter::endStream()
{
   std::cout << "Total Events:" << totalEvent << std::endl;
   std::cout << "Muon Events: " << muonEvents << ";  Electron Events: " << elecEvents << std::endl;
   for( int i = 0 ; i< 10 ; ++i ){
      std::cout << muonCount[i] << "  " ;
   } 
   std::cout << std::endl;
   for( int i = 0 ; i < 10 ; ++i ) {
      std::cout << elecCount[i] << "  " ;  
   }
   std::cout << std::endl;
   std::cout << "Passed Events:" << passedEvent << std::endl ; 
}

void ggChannelFilter::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault( desc );
}
DEFINE_FWK_MODULE( ggChannelFilter );

//------------------------------------------------------------------------------ 
//   Main control flow
//------------------------------------------------------------------------------
bool ggChannelFilter::filter( edm::Event& iEvent, const edm::EventSetup& iSetup )
{
   _jetList.clear();
   _bjetList.clear();
   _vetoMuonList.clear();
   _vetoElecList.clear();
   _selcElecList.clear();
   _selcMuonList.clear();
   //------------------------------------------------------------------------------ 
   //   Getting required Objects
   //------------------------------------------------------------------------------
   iEvent.getByLabel( _beamspotsrc , _rawBeamSpot       ) ;
   iEvent.getByLabel( _muonsrc     , _rawMuonList       ) ;
   iEvent.getByLabel( _elecsrc     , _rawElectronList   ) ;
   iEvent.getByLabel( _jetsrc      , _rawJetList        ) ;
   iEvent.getByLabel( _vertexsrc   , _rawVertexList     ) ;
   iEvent.getByLabel( _convsrc     , _rawConversionList ) ;
   iEvent.getByLabel( _rhosrc      , _rawRho            ) ;

   totalEvent++;
   if( !getPrimaryVertex(iEvent, iSetup) ) { return false; }
   if( !passMuonCleaning(iEvent, iSetup) ) { return false; }
   if( !passElectronCleaning(iEvent, iSetup) ) { return false; }
   if( !passJetCleaning(iEvent, iSetup) ) { return false; }
   if( !passEventSelection(iEvent, iSetup) ) { return false; }

   if( _selcMuonList.size() == 1 ) { muonEvents++; }
   if( _selcElecList.size() == 1 ) { elecEvents++; }
   passedEvent++;
   return true;
}

bool ggChannelFilter::getPrimaryVertex( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   bool gotPV = false;
   const auto& VertexList = *(_rawVertexList.product()) ;
   for( const auto& vertex : VertexList ){
      if( !gotPV && isGoodPV( vertex ) ){
         _primaryVertex = vertex ;
         gotPV=true;
         break;
      }
   }
   return gotPV;
}


bool ggChannelFilter::passMuonCleaning( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   const auto& MuonList = *(_rawMuonList.product()) ;
   for( const auto& muon : MuonList ){
      if( isSelcMuon( muon ) ){
         _selcMuonList.push_back( &muon );
      }else if( isVetoMuon( muon ) ){
         _vetoMuonList.push_back( &muon ) ;
      } 
   }
   return true;   
}

bool ggChannelFilter::passElectronCleaning( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   const auto& ElectronList = *(_rawElectronList.product());
   ElectronEffectiveArea::ElectronEffectiveAreaTarget EATarget = ElectronEffectiveArea::kEleEAFall11MC ; 
   for ( const auto& elec : ElectronList ){
      bool passSelc = isSelcElectron(
            elec,
            _rawConversionList , 
            *(_rawBeamSpot.product()) , 
            _rawVertexList , 
            *(_rawRho.product()) , 
            EATarget  );
      
      bool passVeto = isVetoElectron(
            elec,
            _rawConversionList , 
            *(_rawBeamSpot.product()) , 
            _rawVertexList , 
            *(_rawRho.product()),
            EATarget  );

      if( passSelc ){
         _selcElecList.push_back( &elec ) ;
      }else if ( passVeto ) {
         _vetoElecList.push_back( &elec ) ;
      }
   }
   return true;
}

bool ggChannelFilter::passJetCleaning( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   const auto& JetList = *(_rawJetList.product());
   for( const auto& jet : JetList ){
      if( isSelcJet( jet ) ){
         if( jet.bDiscriminator( "pfCombinedSecondaryVertexV2BTags" ) > 0.89 ) {
            _bjetList.push_back( &jet );
         }else{
            _ljetList.push_back( &jet );
         }
      }
   }
   if( _bjetList.size() < 1 ) { return false ; } 
   if( _ljetList.size() + _bjetList.size() < 6 ) { return false; }

   bool bjetPassPt = false; 
   bool ljetPassPt = false; 
   for( const auto& jet : _bjetList ){
      if( jet->pt() > 35. ) { bjetPassPt=true; }  
   }
   for( const auto& jet : _ljetList ){
      if( jet->pt() > 3.5 ) { ljetPassPt=true; } 
   }
   if( !bjetPassPt ){ return false; }
   if( !ljetPassPt ){ return false; }
   return true;
}

bool ggChannelFilter::passEventSelection( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   if( _selcMuonList.size() == 1 ){
      if( !_vetoMuonList.empty() || 
          !_vetoElecList.empty() ||
          !_selcElecList.empty() ) { 
         return false; }
   } else if( _selcElecList.size() == 1 ){
      if( !_vetoMuonList.empty()  ||
          !_vetoElecList.empty()  ||
          !_selcMuonList.empty() ) {
         return false; }
   } else { 
      return false; }
   if( _jetList.size() < 6 ) {
      return false;
   } else {
      unsigned int btag_count = 0 ;
      for( const auto jet : _jetList ){
         if( jet->bDiscriminator("pfCombinedSecondaryVertexV2BJetTags") > 0.89 ){
            btag_count++; }
      }
      if( btag_count < 1 ) { return false; }
   } 
   return true;
}

