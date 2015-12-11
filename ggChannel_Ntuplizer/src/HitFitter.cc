/*******************************************************************************
 *
 *  Filename    : HitFitter.cc
 *  Description : Implementations of HitFitter class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/ggChannel_Ntuplizer/interface/HitFitter.h"

#include "TopQuarkAnalysis/TopHitFit/interface/fourvec.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Defaults_Text.h"

#include <algorithm>
using namespace hitfit;
using namespace std;
//------------------------------------------------------------------------------ 
//   Constant variables
//------------------------------------------------------------------------------
#define DEFAULT_W_MASS    80.4
#define DEFAULT_TOP_MASS   0.0
static const edm::FileInPath defaultFitter( "TstarAnalysis/ggChannel_Ntuplizer/data/top_gluon.txt" );
static const edm::FileInPath defaultElecFile( "TopQuarkAnalysis/TopggChannel_Ntuplizer/data/resolution/tqafElectronResolution.txt" );
static const edm::FileInPath defaultMuonFile( "TopQuarkAnalysis/TopggChannel_Ntuplizer/data/resolution/tqafMuonResolution.txt" );
static const edm::FileInPath defaultLJetFile( "TopQuarkAnalysis/TopggChannel_Ntuplizer/data/resolution/tqafUdscJetResolution.txt" );
static const edm::FileInPath defaultBJetFile( "TopQuarkAnalysis/TopggChannel_Ntuplizer/data/resolution/tqafBJetResolution.txt" ); 

#define MAX_HIT_FIT_JETS  6

//------------------------------------------------------------------------------ 
//   Constructor and Destructor
//------------------------------------------------------------------------------
HitFitter::HitFitter( const edm::ParameterSet& iConfig )
{
   const edm::FileInPath fitterFile = iConfig.getUntrackedParameter<edm::FileInPath>( "fitterConfig" , defaultFitter );
   double fitter_lepWMass = iConfig.getUntrackedParameter<double>( "fittingLeptonicWMass" ,  DEFAULT_W_MASS );
   double fitter_hadWMass = iConfig.getUntrackedParameter<double>( "fittingHadronicWMass" ,  DEFAULT_W_MASS );
   double fitter_topMass  = iConfig.getUntrackedParameter<double>( "fittingTopMass" ,  DEFAULT_TOP_MASS );
   _top_fitter = new Top_Fit( Defaults_Text(fitterFile.fullPath()) , fitter_lepWMass , fitter_hadWMass , fitter_topMass );

   const edm::FileInPath elecResolutionFile = iConfig.getUntrackedParameter<edm::FileInPath>( "electronResolution" , defaultElecFile );
   const edm::FileInPath muonResolutionFile = iConfig.getUntrackedParameter<edm::FileInPath>( "muonResolution" , defaultMuonFile );
   const edm::FileInPath ljetResolutionFile = iConfig.getUntrackedParameter<edm::FileInPath>( "lightJetResolution" , defaultLJetFile );
   const edm::FileInPath bjetResolutionFile = iConfig.getUntrackedParameter<edm::FileInPath>( "bJetResolution" , defaultBJetFile );
   _electronResolution = new EtaDepResolution( elecResolutionFile.fullPath() );
   _muonResolution     = new EtaDepResolution( muonResolutionFile.fullPath() );
   _lightJetResolution = new EtaDepResolution( ljetResolutionFile.fullPath() );
   _bJetResolution     = new EtaDepResolution( bjetResolutionFile.fullPath() );
   _met_KtResolution   = new Resolution("0,0,12");
}

HitFitter::~HitFitter()
{
   delete _top_fitter;
   delete _electronResolution;
   delete _muonResolution;
   delete _lightJetResolution;
   delete _bJetResolution;
   delete _met_KtResolution;
}

//------------------------------------------------------------------------------ 
//   Main control - Runing HitFit permutations
//------------------------------------------------------------------------------
void HitFitter::RunPermutations() 
{
   // Dummy variables for storing fitting results;
   bool   solveNeutrino;
   double fittedWHadronMass;
   double fittedTopMass;
   double fittedTopMass2;
   double sumTopMass;
   double chiSquare;
   Column_Vector pullx;
   Column_Vector pully;

   // Dummy event only handling MET and Lepton
   // Jets are handled in the permutation loop
   Lepjets_Event hitFitEventTemplate( 0,0 );

   //----- Setting up MET  --------------------------------------------------------
   AddHitFitMET( &hitFitEventTemplate , _metPtr );

   //----- Setting up Leptons  ----------------------------------------------------
   for( const auto& muon : *_muonListPtr ){
      AddHitFitLepton( &hitFitEventTemplate, muon );
   }
   for( const auto& elec : *_elcteoncListPtr ){
      AddHitFitLepton( &hitFitEventTemplate, elec );
   }

   //----- Setting up Jet Labels  -------------------------------------------------
   const unsigned numberOfJets = _btagJetListPtr->size() + _lightJetListPtr->size();
   const unsigned hitfitJetCount = (numberOfJets<MAX_HIT_FIT_JETS)?numberOfJets:MAX_HIT_FIT_JETS;
   vector<int> jet_type_list( hitfitJetCount , hitfit::unknown_label ) ;
   jet_type_list[0] = hitfit::lepb_label; 
   jet_type_list[1] = hitfit::hadb_label;
   jet_type_list[2] = hitfit::hadw1_label;
   jet_type_list[3] = hitfit::hadw2_label;
   jet_type_list[4] = hitfit::gluon1_label;
   jet_type_list[5] = hitfit::gluon2_label;

   //----- Permute jet labels  ---------------------------------------------------
   do {
      if( !CheckBTagOrder( jet_type_list ) ) { continue; }

      Lepjets_Event hitFitEvent = hitFitEventTemplate;
      unsigned i = 0 ;
      for( const auto jet : *_btagJetListPtr ){
         AddHitFitJet( &hitFitEvent, jet, jet_type_list[i]); ++i; }
      for( const auto jet : *_lightJetListPtr ){
         AddHitFitJet( &hitFitEvent, jet, jet_type_list[i]); ++i;
         if( i >= hitfitJetCount ){ break; }
      }
      hitFitEvent.set_jet_types( jet_type_list );

      // Running Hit Fit
      chiSquare = _top_fitter->fit_one_perm( 
            hitFitEvent,
            solveNeutrino,
            fittedWHadronMass,
            fittedTopMass,
            fittedTopMass2,
            sumTopMass,
            pullx,
            pully );

      // Store all results for now
      _resultList.push_back( Fit_Result( 
               chiSquare,
               hitFitEvent, 
               pullx,
               pully,
               fittedWHadronMass,
               fittedTopMass,
               fittedTopMass2,
               sumTopMass ));
      
   } while ( next_permutation( jet_type_list.begin() , jet_type_list.end() ) );
}

void HitFitter::ClearAll()
{
   // Deleting all per-event results
   _resultList.clear();
   _elcteoncListPtr = NULL;
   _muonListPtr     = NULL;
   _btagJetListPtr  = NULL;
   _lightJetListPtr = NULL;
   _metPtr          = NULL;
}

const hitfit::Fit_Results& HitFitter::getBestResult() const
{
   unsigned min_index  = -1;
   double min_ChiSquare = 10000000.;
   double this_ChiSquare;

   for( unsigned i = 0; i < _resultList.size() ; ++i ){
      this_ChiSquare = _resultList[i].chisq() ;
      if( this_ChiSquare < min_ChiSquare && this_ChiSquare > 0.0 ){
         min_index = i;
         min_ChiSquare = this_ChiSquare;
      }
   }
   return _resultList[min_index];
}

//------------------------------------------------------------------------------ 
//   Translator private functions
//------------------------------------------------------------------------------
void HitFitter::AddHitFitMetMET( Lepjets_Event* hitFitEvent, const pat::MET* met ) const 
{
   hitFitEvent.met()    = Fourvec( met->px() , met->py() , 0 , met->pt() );
   hitFitEvent.kt_res() = *( _met_KtResolution );
}

void HitFitter::AddHitFitLepton( Lepjets_Event* hitFitEvent , const pat::Muon* mu ) const
{
   double muon_eta = mu->eta() ; // Required! For type conversion
   Fourvec lep_p4( mu->px() , mu->py() , mu->pz() , mu->energy() );
   Vector_Resolution lep_resolution = _muonResolution->GetResolution( muon_eta );
   hitFitEvent->add_lep( Lepjets_Event_Lep(lep_p4 , 0 , lep_resolution) ); //label = 0 for primary lepton
}

void HitFitter::AddHitFitLepton( Lepjets_Event* hitFitEvent, const reco::GsfElectron* el ) const
{
   double elec_eta = el->eta(); // Required! For type conversion
   Fourvec lep_p4( el->px() , el->py() , el->pz() , el->energy() );
   Vector_Resolution lep_resolution = _electronResolution->GetResolution( elec_eta );
   hitFitEvent->add_lep( Lepjets_Event_Lep(lep_p4 , 0 , lep_resolution) ); //label = 0 for primary lepton
}

void HitFitter::AddHitFitJet( Lepjets_Event* hitFitEvent, const pat::Jet* jet , const int type ) const
{
   double jet_eta = jet->eta();
   Fourvec jetp4( jet->px() , jet->py() , jet->pz(), jet->energy() );
   Vector_Resolution jet_resolution ;
   if( type == hitfit::hadb_label || type == hitfit::lepb_label ){
      jet_resolution = _bJetResolution->GetResolution( jet_eta );
   } else {
      jet_resolution = _lightJetResolution->GetResolution( jet_eta );
   }
   hitFitEvent->add_jet( Lepjets_Event_Jet(jetp4 , type , jet_resolution) );
}



