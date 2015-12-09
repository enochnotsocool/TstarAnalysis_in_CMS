/*******************************************************************************
 *
 *  Filename    : Ntuplizer_HitFit.cc
 *  Description : HitFIt related packages
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/Ntuplizer/interface/Ntuplizer.h"

#include "TopQuarkAnalysis/TopHitFit/interface/fourvec.h"
#include "TopQuarkAnalysis/TopHitFit/interface/EtaDepResolution.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Top_Decaykin.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Defaults_Text.h"

#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
using namespace hitfit;

//------------------------------------------------------------------------------ 
//   Constant variables
//------------------------------------------------------------------------------
#define DEFAULT_W_MASS    80.4
#define DEFAULT_TOP_MASS   0.0
static const edm::FileInPath defaultFitter( "TstarAnalysis/Ntuplizer/data/top_gluon.txt" );
static const edm::FileInPath defaultElecFile( "TopQuarkAnalysis/TopHitFit/data/resolution/tqafElectronResolution.txt" );
static const edm::FileInPath defaultMuonFile( "TopQuarkAnalysis/TopHitFit/data/resolution/tqafMuonResolution.txt" );
static const edm::FileInPath defaultLJetFile( "TopQuarkAnalysis/TopHitFit/data/resolution/tqafUdscJetResolution.txt" );
static const edm::FileInPath defaultBJetFile( "TopQuarkAnalysis/TopHitFit/data/resolution/tqafBJetResolution.txt" ); 

#define MAX_HIT_FIT_JETS  6

//------------------------------------------------------------------------------ 
//   Variable initialization and cleaning
//------------------------------------------------------------------------------
void Ntuplizer::InitHitFit( const edm::ParameterSet& iConfig )
{
   if( _debug ) { cerr << "Constructing HitFit objects..." << flush; }
   const edm::FileInPath fitterFile = iConfig.getUntrackedParameter<edm::FileInPath>( "fitterConfig" , defaultFitter );
   double fitter_lepWMass = iConfig.getUntrackedParameter<double>( "fittingLeptonicWMass" ,  DEFAULT_W_MASS );
   double fitter_hadWMass = iConfig.getUntrackedParameter<double>( "fittingHadronicWMass" ,  DEFAULT_W_MASS );
   double fitter_topMass  = iConfig.getUntrackedParameter<double>( "fittingTopMass" ,  DEFAULT_TOP_MASS );
   _top_fitter = new Top_Fit( Defaults_Text(fitterFile.fullPath()) , fitter_lepWMass , fitter_hadWMass , fitter_topMass );
   if(_debug ) { cerr << "... Done Top_Fit ..." << flush ; }

   const edm::FileInPath elecResolutionFile = iConfig.getUntrackedParameter<edm::FileInPath>( "electronResolution" , defaultElecFile );
   const edm::FileInPath muonResolutionFile = iConfig.getUntrackedParameter<edm::FileInPath>( "muonResolution" , defaultMuonFile );
   const edm::FileInPath ljetResolutionFile = iConfig.getUntrackedParameter<edm::FileInPath>( "lightJetResolution" , defaultLJetFile );
   const edm::FileInPath bjetResolutionFile = iConfig.getUntrackedParameter<edm::FileInPath>( "bJetResolution" , defaultBJetFile );
   _electronResolution = new EtaDepResolution( elecResolutionFile.fullPath() );
   _muonResolution     = new EtaDepResolution( muonResolutionFile.fullPath() );
   _lightJetResolution = new EtaDepResolution( ljetResolutionFile.fullPath() );
   _bJetResolution     = new EtaDepResolution( bjetResolutionFile.fullPath() );
 
   _met_KtResolution = new Resolution("0,0,12");
   if( _debug ) { cerr << " Done Resolutions!" << endl; }

   _hitfitBranches.registerVariables( _tree );
}

void Ntuplizer::ClearHitFit()
{
   delete _top_fitter;
   delete _electronResolution;
   delete _muonResolution;
   delete _lightJetResolution;
   delete _bJetResolution;
   delete _met_KtResolution;
}

//------------------------------------------------------------------------------ 
//   Hit Fit Control Flow
//------------------------------------------------------------------------------
void Ntuplizer::RunHitFit( const edm::Event& iEvent ) 
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
   AddMET( hitFitEventTemplate , *(_metList.product()->begin()) );

   //----- Setting up Leptons  ----------------------------------------------------
   for( const auto& muon : _selectedMuonList ){
      AddLepton( hitFitEventTemplate, *muon );
   }
   for( const auto& elec : _selectedElectronList ){
      AddLepton( hitFitEventTemplate, *elec );
   }

   //----- Setting up Jet Labels  -------------------------------------------------
   const unsigned numberOfJets = _selectedLJetList.size() + _selectedBJetList.size();
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

      if( _debug > 1 ){
         cerr << "\t[1] JetType: " ;
         for( unsigned i = 0 ; i < jet_type_list.size() ; ++i ){
            cerr << " " << jet_type_list[i] ;
         }
         cerr << endl;
      } 

      Lepjets_Event hitFitEvent = hitFitEventTemplate;
      unsigned i = 0 ;
      for( const auto& jet : _selectedBJetList ){
         AddJet( hitFitEvent, *jet, jet_type_list[i]); ++i; }
      for( const auto& jet : _selectedLJetList ){
         AddJet( hitFitEvent, *jet, jet_type_list[i]); ++i;
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
      _fitResultList.push_back( Fit_Result( 
               chiSquare,
               hitFitEvent, 
               pullx,
               pully,
               fittedWHadronMass,
               fittedTopMass,
               fittedTopMass2,
               sumTopMass ));
      
   } while ( next_permutation( jet_type_list.begin() , jet_type_list.end() ) );
   if( _debug ) { cerr << "Finnish permutations!" << endl; }

}

//------------------------------------------------------------------------------ 
//   Ntuplization
//------------------------------------------------------------------------------
void Ntuplizer::AddHitFitResults()
{
   double   this_ChiSquare;
   double   min_ChiSquare = 10000000.;
   unsigned min_index = -1;

   if( _debug ) { cerr << "Getting HitFit results!" << endl; }

   //----- Getting Best results only  ---------------------------------------------
   for( unsigned i = 0; i < _fitResultList.size() ; ++i ){
      this_ChiSquare = _fitResultList[i].chisq() ;
      if( this_ChiSquare < min_ChiSquare && this_ChiSquare > 0.0 ){
         min_index = i;
         min_ChiSquare = this_ChiSquare;
      }
   }
   const Fit_Result& best = _fitResultList[min_index];

   const math::XYZTLorentzVector fittedLepton( best.ev().lep(0).p() );
   const math::XYZTLorentzVector fittedNeutrino( best.ev().met() );
   const math::XYZTLorentzVector fittedKt    ( best.ev().kt() );
   const math::XYZTLorentzVector fittedLepW  ( hitfit::Top_Decaykin::lepw( best.ev() ) );
   const math::XYZTLorentzVector fittedLepTop( hitfit::Top_Decaykin::lept( best.ev() ) );
   const math::XYZTLorentzVector fittedHadW  ( hitfit::Top_Decaykin::hadw( best.ev() ) );
   const math::XYZTLorentzVector fittedHadTop( hitfit::Top_Decaykin::hadt( best.ev() ) );

   _hitfitBranches.TstarMass      = best.mt();
   _hitfitBranches.TstarMassSigma = best.sigmt();
   _hitfitBranches.ChiSquare      = best.chisq();

   _hitfitBranches.Lepton_Pt     = fittedLepton.pt();
   _hitfitBranches.Lepton_Eta    = fittedLepton.eta();
   _hitfitBranches.Lepton_Phi    = fittedLepton.phi();
   _hitfitBranches.Lepton_Energy = fittedLepton.energy();
   
   _hitfitBranches.Neutrino_Pt     = fittedNeutrino.pt() ;
   _hitfitBranches.Neutrino_Eta    = fittedNeutrino.eta();
   _hitfitBranches.Neutrino_Phi    = fittedNeutrino.phi();
   _hitfitBranches.Neutrino_Energy = fittedNeutrino.energy();

   _hitfitBranches.Leptonic_W_Pt     = fittedLepW.pt();       
   _hitfitBranches.Leptonic_W_Eta    = fittedLepW.eta();       
   _hitfitBranches.Leptonic_W_Phi    = fittedLepW.phi();       
   _hitfitBranches.Leptonic_W_Energy = fittedLepW.energy();       
   _hitfitBranches.Hadronic_W_Pt     = fittedHadW.pt();
   _hitfitBranches.Hadronic_W_Eta    = fittedHadW.eta();
   _hitfitBranches.Hadronic_W_Phi    = fittedHadW.phi();
   _hitfitBranches.Hadronic_W_Energy = fittedHadW.energy();

   _hitfitBranches.Leptonic_Top_Pt      = fittedLepTop.pt();
   _hitfitBranches.Leptonic_Top_Eta     = fittedLepTop.eta();
   _hitfitBranches.Leptonic_Top_Phi     = fittedLepTop.phi();
   _hitfitBranches.Leptonic_Top_Energy  = fittedLepTop.energy();
   _hitfitBranches.Hadronic_Top_Pt      = fittedHadTop.pt() ;
   _hitfitBranches.Hadronic_Top_Eta     = fittedHadTop.eta() ;
   _hitfitBranches.Hadronic_Top_Phi     = fittedHadTop.phi() ;
   _hitfitBranches.Hadronic_Top_Energy  = fittedHadTop.energy() ;

   _fitResultList.clear();
}

//------------------------------------------------------------------------------ 
//   Object Translation
//------------------------------------------------------------------------------
void Ntuplizer::AddMET( Lepjets_Event& hitFitEvent, const pat::MET& met )
{
   hitFitEvent.met()    = Fourvec( met.px() , met.py() , 0 , met.pt() );
   hitFitEvent.kt_res() = *( _met_KtResolution );
}

void Ntuplizer::AddLepton( Lepjets_Event& hitFitEvent , const pat::Muon& mu )
{
   double muon_eta = mu.eta() ; // Required! For type conversion
   Fourvec lep_p4( mu.px() , mu.py() , mu.pz() , mu.energy() );
   Vector_Resolution lep_resolution = _muonResolution->GetResolution( muon_eta );
   hitFitEvent.add_lep( Lepjets_Event_Lep(lep_p4 , 0 , lep_resolution) ); //label = 0 for primary lepton
}

void Ntuplizer::AddLepton( Lepjets_Event& hitFitEvent, const pat::Electron& el )
{
   double elec_eta = el.eta();
   Fourvec lep_p4( el.px() , el.py() , el.pz() , el.energy() );
   Vector_Resolution lep_resolution = _electronResolution->GetResolution( elec_eta );
   hitFitEvent.add_lep( Lepjets_Event_Lep(lep_p4 , 0 , lep_resolution) ); //label = 0 for primary lepton
}


void Ntuplizer::AddJet( Lepjets_Event& hitFitEvent, const pat::Jet& jet , const int type )
{
   double jet_eta = jet.eta();
   Fourvec jetp4( jet.px() , jet.py() , jet.pz(), jet.energy() );
   Vector_Resolution jet_resolution ;
   if( type == hitfit::hadb_label || type == hitfit::lepb_label ){
      jet_resolution = _bJetResolution->GetResolution( jet_eta );
   } else {
      jet_resolution = _lightJetResolution->GetResolution( jet_eta );
   }
   hitFitEvent.add_jet( Lepjets_Event_Jet(jetp4 , type , jet_resolution) );
}

bool Ntuplizer::CheckBTagOrder( const vector<int>& jet_type_list )
{
   //----- First tag must be b tag  -----------------------------------------------
   if( jet_type_list[0] == hitfit::lepb_label ){ return true; }
   if( jet_type_list[0] == hitfit::hadb_label ){ return true; }
   return false;
}

