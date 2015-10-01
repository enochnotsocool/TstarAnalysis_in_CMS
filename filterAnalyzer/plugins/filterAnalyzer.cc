/*******************************************************************************
 *
 *  Filename    : filterAnalyzer.cc
 *  Description : Control of analyzer
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Details     : The main job is to determine the selection efficiencies of
 *                various cuts. The selection flow would be nearly the same
 *                as the edm filter
 *
*******************************************************************************/
#include "TstarAnalysis/filterAnalyzer/interface/filterAnalyzer.h"
#include "TstarAnalysis/Selection/interface/Selection.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//------------------------------------------------------------------------------ 
//   helper Variables
//------------------------------------------------------------------------------
static edm::Service<TFileService> fs;
static TFileDirectory results ;

//------------------------------------------------------------------------------
//   Constructor and Destructor
//------------------------------------------------------------------------------
filterAnalyzer::filterAnalyzer( const edm::ParameterSet& iConfig )
{
   _muonsrc   = iConfig.getParameter<edm::InputTag>( "muonsrc"   ) ;
   _elecsrc   = iConfig.getParameter<edm::InputTag>( "elecsrc"   ) ;
   _jetsrc    = iConfig.getParameter<edm::InputTag>( "jetsrc"    ) ;
   _vertexsrc = iConfig.getParameter<edm::InputTag>( "vertexsrc" ) ;
   _rhosrc    = iConfig.getParameter<edm::InputTag>( "rhosrc"  ) ;
   _beamspotsrc = iConfig.getParameter<edm::InputTag>( "beamspotsrc" );
   _convsrc   = iConfig.getParameter<edm::InputTag> ( "convsrc" );

   results = TFileDirectory( fs->mkdir( "results" ) );
   _selcMuonCount = fs->make<TH1F>( "SelecMuon" , "SelecMuon" , 10 , 0 , 10 );
   _selcElecCount = fs->make<TH1F>( "SelecElec" , "SelecElec" , 10 , 0 , 10 );
   _selcJetCount  = fs->make<TH1F>( "SelecJet"  , "SelecJet"  , 10 , 0 , 10 );
   _eventCount    = fs->make<TH1F>( "Event"     , "Event"     , 10 , 0 , 10 ) ;
}


filterAnalyzer::~filterAnalyzer()
{
}

//------------------------------------------------------------------------------
//   Main control flow
//------------------------------------------------------------------------------
void filterAnalyzer::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
   _ljetList.clear();
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

   getPrimaryVertex(iEvent, iSetup     );
   passMuonCleaning(iEvent, iSetup     );
   passElectronCleaning(iEvent, iSetup );
   passJetCleaning(iEvent, iSetup      );
   passEventSelection(iEvent, iSetup   );

}

bool filterAnalyzer::getPrimaryVertex( const edm::Event& iEvent , const edm::EventSetup& iSetup )
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


bool filterAnalyzer::passMuonCleaning( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   const auto& MuonList = *(_rawMuonList.product()) ;
   for( const auto& muon : MuonList ){
      if( isSelcMuon( muon , _primaryVertex, _selcMuonCount ) ){
         _selcMuonList.push_back( &muon );
      }else if( isVetoMuon( muon ) ){
         _vetoMuonList.push_back( &muon ) ;
      } 
   }
   return true;   
}

bool filterAnalyzer::passElectronCleaning( const edm::Event& iEvent , const edm::EventSetup& iSetup )
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
            EATarget , 
            _selcElecCount );
      
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

bool filterAnalyzer::passJetCleaning( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   const auto& JetList = *(_rawJetList.product());
   for( const auto& jet : JetList ){
      if( isSelcJet( jet , _selcElecList, _selcMuonList , _selcJetCount) ){
         if( jet.bDiscriminator( "pfCombinedSecondaryVertexV2BJetTags" ) > 0.89 ) {
            _bjetList.push_back( &jet );
         }else{
            _ljetList.push_back( &jet );
         }
      }
   }
   
   if( _bjetList.size() < 2 ) { return false ; } 
   if( _ljetList.size() + _bjetList.size() < 6 ) { return false; }

   return true;
}

bool filterAnalyzer::passEventSelection( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   bool muonEvt = ( _selcMuonList.size() == 1 && _selcElecList.size() == 0 );
   bool elecEvt = ( _selcMuonList.size() == 0 && _selcElecList.size() == 1 );

   _eventCount->Fill(0);
   if( !muonEvt && !elecEvt ) { return false; }
   _eventCount->Fill(1);
   if( !_vetoElecList.empty() || !_vetoMuonList.empty() ){ return false;}
   _eventCount->Fill(2);
   if( _bjetList.size() < 2 ) { return false; }
   _eventCount->Fill(3);
   if( _ljetList.size() + _bjetList.size() < 6 ) { return false; }
   _eventCount->Fill(4);
   
   bool bjetPassPt = false; 
   bool ljetPassPt = false; 
   for( const auto& jet : _bjetList ){
      if( jet->pt() > 35. ) { 
         bjetPassPt=true; break; }  
   }
   for( const auto& jet : _ljetList ){
      if( jet->pt() > 35. ) { 
         ljetPassPt=true; break; } 
   }
   if( !bjetPassPt ){ return false; }
   if( !ljetPassPt ){ return false; }
   _eventCount->Fill(5);
   return true;
}

//------------------------------------------------------------------------------
//   ED Analyser requirements
//------------------------------------------------------------------------------
void filterAnalyzer::beginJob() {}
void filterAnalyzer::endJob() {}
void filterAnalyzer::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault( desc );
}
DEFINE_FWK_MODULE( filterAnalyzer );
