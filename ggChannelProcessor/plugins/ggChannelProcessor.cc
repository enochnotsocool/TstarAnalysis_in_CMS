/*******************************************************************************
 *
 *  Filename    : ggChannelProcessor.cc
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

#include "TstarAnalysis/ggChannelProcessor/interface/ggChannelProcessor.h"
#include "TstarAnalysis/Selection/interface/Selection.h"
#include "TstarAnalysis/RootFormat/interface/MiniJetBranches.h"
//------------------------------------------------------------------------------ 
//   Helper variables
//------------------------------------------------------------------------------ 
static edm::Service<TFileService> fs;
static TFileDirectory results ;

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
ggChannelProcessor::ggChannelProcessor( const edm::ParameterSet& iConfig )
{
   _muonsrc     = iConfig.getParameter<edm::InputTag>( "muonsrc"     ) ;
   _elecsrc     = iConfig.getParameter<edm::InputTag>( "elecsrc"     ) ;
   _jetsrc      = iConfig.getParameter<edm::InputTag>( "jetsrc"      ) ;
   _metsrc      = iConfig.getParameter<edm::InputTag>( "metsrc"      ) ;
   _vertexsrc   = iConfig.getParameter<edm::InputTag>( "vertexsrc"   ) ;
   _rhosrc      = iConfig.getParameter<edm::InputTag>( "rhosrc"      ) ;
   _beamspotsrc = iConfig.getParameter<edm::InputTag>( "beamspotsrc" ) ;
   _convsrc     = iConfig.getParameter<edm::InputTag>( "convsrc"     ) ;
   _pileupsrc   = iConfig.getParameter<edm::InputTag>( "pileupsrc"   ) ;
   
   results = TFileDirectory( fs->mkdir( "results" ) );
   _tree =  fs->make<TTree>( "EventVariables" , "EventVariables" );
   _eventBranches.registerVariables( _tree );
   _muonBranches.registerVariables( _tree );
   _elecBranches.registerVariables( _tree );
   _jetBranches.registerVariables( _tree  );
}

ggChannelProcessor::~ggChannelProcessor()
{}

//------------------------------------------------------------------------------ 
//   Main control flow
//------------------------------------------------------------------------------
void ggChannelProcessor::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup )
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
   iEvent.getByLabel( _metsrc      , _rawMETList        ) ;
   iEvent.getByLabel( _pileupsrc   , _rawPileupList     ) ;
   GetSelectionObjects();

   FillTree( iEvent );   
}

void ggChannelProcessor::GetSelectionObjects()
{
   // std::cout << "Begin object selection" << std::endl;
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
   // std::cout << "Done Object selection " << std::endl;
}


bool ggChannelProcessor::isMuonEvent(){ return (_selectedMuonList.size()==1 && _selectedElecList.size()==0);}
bool ggChannelProcessor::isElectronEvent() { return (_selectedMuonList.size()==0 && _selectedElecList.size()==1); }

//------------------------------------------------------------------------------ 
//   ED Processor requirements
//------------------------------------------------------------------------------
void ggChannelProcessor::beginJob(){}
void ggChannelProcessor::endJob() {}
void ggChannelProcessor::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault( desc );
}
DEFINE_FWK_MODULE( ggChannelProcessor );
