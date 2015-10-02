/*******************************************************************************
 *
 *  Filename    : ggChannelFilter.cc
 *  Description : ED Plugini setups for ggChannel Event Selection
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include <iostream>
#include "TstarAnalysis/ggChannelFilter/interface/ggChannelFilter.h"
#include "TstarAnalysis/Selection/interface/Selection.h"
//----- File output  -----------------------------------------------------------
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//------------------------------------------------------------------------------ 
//   helper Variables
//------------------------------------------------------------------------------
static edm::Service<TFileService> fs;
static TFileDirectory results ;
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
   
   results = TFileDirectory( fs->mkdir( "results" ) );
   _selcMuonCount = fs->make<TH1F>( "SelectionMuon"     , "SelectionMuon"     , 10 , 0 , 10 );
   _selcElecCount = fs->make<TH1F>( "SelectionElectron" , "SelectionElectron" , 10 , 0 , 10 );
   _selcJetCount  = fs->make<TH1F>( "SeletionJet"       , "SelectionJet"      , 10 , 0 , 10 );
   _vetoMuonCount = fs->make<TH1F>( "VetoMuon"          , "VetoMuon"          , 10 , 0 , 10 );
   _vetoElecCount = fs->make<TH1F>( "VetoElectron"      , "VetoElectron"      , 10 , 0 , 10 );
   _trackIsoHist  = fs->make<TH1F>( "traskIso"          , "trackIso"          , 50 , 0 , 5  );
   _muEventCount  = fs->make<TH1F>( "MuEvent"           , "Event"             , 10 , 0 , 10 );
   _elEventCount  = fs->make<TH1F>( "ElecEvent"         , "ElecEvent"         , 10 , 0 , 10 );

}


ggChannelFilter::~ggChannelFilter()
{ }

void ggChannelFilter::beginStream( edm::StreamID )
{ }

void ggChannelFilter::endStream()
{
   std::cout << "Total Events: " << _muEventCount->GetBinContent(1) << endl; 
   std::cout << "Muon  Events: " << _muEventCount->GetBinContent(6) << endl; 
   std::cout << "Electron Events: " << _elEventCount->GetBinContent(6) << endl; 
}

void ggChannelFilter::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault( desc );
}

//------------------------------------------------------------------------------ 
//   Main control flow
//------------------------------------------------------------------------------
bool ggChannelFilter::filter( edm::Event& iEvent, const edm::EventSetup& iSetup )
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

   getPrimaryVertex(iEvent, iSetup          ) ;
   passMuonCleaning(iEvent, iSetup          );
   passElectronCleaning(iEvent, iSetup      );
   passJetCleaning(iEvent, iSetup           );
   return passEventSelection(iEvent, iSetup ) ;
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
      _trackIsoHist->Fill( muon.trackIso() );
      bool selcMu = isSelcMuon( muon , _primaryVertex , _selcMuonCount ) ;
      bool vetoMu = isVetoMuon( muon , _vetoMuonCount ) ;
      if( selcMu ){
         _selcMuonList.push_back( &muon );
      }else if( vetoMu ){
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
            EATarget , 
            _selcElecCount );

      bool passVeto = isVetoElectron(
            elec,
            _rawConversionList , 
            *(_rawBeamSpot.product()) , 
            _rawVertexList , 
            *(_rawRho.product()),
            EATarget  ,
            _vetoElecCount );

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
      if( isSelcJet( jet , _selcElecList, _selcMuonList, _selcJetCount ) ){
         if( jet.bDiscriminator( "pfCombinedSecondaryVertexV2BJetTags" ) > 0.89 ) {
            _bjetList.push_back( &jet );
         }else{
            _ljetList.push_back( &jet );
         }
      }
   }

   return true;
}

bool ggChannelFilter::passEventSelection( const edm::Event& iEvent , const edm::EventSetup& iSetup )
{
   _muEventCount->Fill(0);
   _elEventCount->Fill(0);

   bool isMuEvent = ( _selcMuonList.size() == 1 && _selcElecList.size() == 0 ); 
   bool isElEvent = ( _selcMuonList.size() == 0 && _selcElecList.size() == 1 ) ;
   if( isMuEvent ) {
      _muEventCount->Fill(1);
   }else if( isElEvent ) {
      _elEventCount->Fill(1);
   } else return false;

   if( _ljetList.size() + _bjetList.size() < 6 ) { return false; }
   if( isMuEvent ) {
      _muEventCount->Fill(2);
   }else if( isElEvent ) {
      _elEventCount->Fill(2); }
   if( _bjetList.size() < 2 ) { return false ; } 
   if( isMuEvent ) {
      _muEventCount->Fill(3);
   }else if( isElEvent ) {
      _elEventCount->Fill(3); }

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
   if( isMuEvent ) {
      _muEventCount->Fill(4);
   }else if( isElEvent ) {
      _elEventCount->Fill(4); }
   if( !ljetPassPt ){ return false; }
   if( isMuEvent ) {
      _muEventCount->Fill(5);
   }else if( isElEvent ) {
      _elEventCount->Fill(5); }
   return true;
}
DEFINE_FWK_MODULE( ggChannelFilter );

