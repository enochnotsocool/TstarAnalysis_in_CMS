/*******************************************************************************
 *
 *  Filename    : ggChannelAnalyzer.cc
 *  Description : Implementation of channel analyzer
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  The implementation will be split up into multiple files,
 *  given the complexity of certain methods, for source of 
 *  private methods, read the header file.
 *
*******************************************************************************/
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TstarAnalysis/ggChannelAnalyzer/interface/ggChannelAnalyzer.h"
#include "TstarAnalysis/Selection/interface/Selection.h"
//------------------------------------------------------------------------------ 
//   Helper variables
//------------------------------------------------------------------------------ 
static edm::Service<TFileService> fs;
static TFileDirectory results ;

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
ggChannelAnalyzer::ggChannelAnalyzer( const edm::ParameterSet& iConfig )
{
   _muonsrc     = iConfig.getParameter<edm::InputTag>( "muonsrc"     ) ;
   _elecsrc     = iConfig.getParameter<edm::InputTag>( "elecsrc"     ) ;
   _jetsrc      = iConfig.getParameter<edm::InputTag>( "jetsrc"      ) ;
   _vertexsrc   = iConfig.getParameter<edm::InputTag>( "vertexsrc"   ) ;
   _rhosrc      = iConfig.getParameter<edm::InputTag>( "rhosrc"      ) ;
   _beamspotsrc = iConfig.getParameter<edm::InputTag>( "beamspotsrc" ) ;
   _convsrc     = iConfig.getParameter<edm::InputTag>( "convsrc"     ) ;
   
   results = TFileDirectory( fs->mkdir( "results" ) );
   _EventConstructedVariables = fs->make<TTree>( "AnalysisVariables" , "AnalysisVariables" );
   _EventConstructedVariables->Branch( "ChiSqMass" , &_chiMass , "ChiSqMass/F" );
}


ggChannelAnalyzer::~ggChannelAnalyzer()
{}

//------------------------------------------------------------------------------ 
//   Main control flow
//------------------------------------------------------------------------------
void ggChannelAnalyzer::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
   _selectedLJetList.clear();
   _selectedBJetList.clear();
   _selectedMuonList.clear();
   _selectedElecList.clear();
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

   GetSelectionObjects();
   _chiMass = computeChiSqMass() ;

   _EventConstructedVariables->Fill();
}

void ggChannelAnalyzer::GetSelectionObjects()
{
   const auto& VertexList = *(_rawVertexList.product());
   for( const auto& vertex : VertexList ){
      if( isGoodPV( vertex ) ){
         _primaryVertex=vertex; break;
      }
   }
   const auto& MuonList = *(_rawMuonList.product()) ;
   for( const auto& muon : MuonList ){
      bool selcMu = isSelcMuon( muon , _primaryVertex ) ;
      if( selcMu ){
         _selectedMuonList.push_back( &muon );
      } 
   }
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
      if( passSelc ){
         _selectedElecList.push_back( &elec ) ;
      }
   }
   
   const auto& JetList = *(_rawJetList.product());
   for( const auto& jet : JetList ){
      if( isSelcJet( jet , _selectedElecList, _selectedMuonList ) ){
         if( jet.bDiscriminator( "pfCombinedSecondaryVertexV2BJetTags" ) > 0.89 ) {
            _selectedBJetList.push_back( &jet );
         }else{
            _selectedLJetList.push_back( &jet );
         }
      }
   }
}

//------------------------------------------------------------------------------ 
//   ED Analyzer requirements
//------------------------------------------------------------------------------
void ggChannelAnalyzer::beginJob(){}
void ggChannelAnalyzer::endJob() {}
void ggChannelAnalyzer::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault( desc );
}
DEFINE_FWK_MODULE( ggChannelAnalyzer );
