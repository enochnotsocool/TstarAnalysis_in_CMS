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

#include <vector>
#include <algorithm>
using namespace std;


void Ntuplizer::RunHitFit( const edm::Event& iEvent ) 
{
   // Dummy variables for storing fitting results;
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
   AddMET( hitFitEventTemplate , *(_metList.product()->begin() );

   //----- Setting up Leptons  ----------------------------------------------------
   for( const auto& muon : _selectedMuonList ){
      AddLepton( hitFitEventTemplate, *muon );
   }
   for( const auto& elec : _selectedElectronList ){
      AddLepton( hitFitEventTemplate, *elec );
   }

   //----- Setting up Jet Labels  -------------------------------------------------
   const unsigned numberOfJets = _selectedJetList.size() + _selectedBJetList.size();
   vector<int> jet_type_list( numberOfJets , hitfit::unknown_label ) ;
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
      for( const auto& jet : _selectedBJetList ){
         AddJet( hitFitEvent, *jet, jet_type_list[i]); ++i; }
      for( const auto& jet : _selectedLJetList ){
         AddJet( hitFitEvent, *jet, jet_type_list[i]); ++i; }
      hitFitEvent.set_jet_types( jet_type_list );

      // Running Hit Fit
      chiSquare = _top_fitter.fit_one_perm( 
            hitFitEvent,
            true, // Solve nu by Top_Fit
            fittedWHadronMass, // Storing results
            fittedTopMass,
            fittedTopMass2,
            sumTopMass,
            pullx,
            pully );

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
   
   //----- Cleaning up  -----------------------------------------------------------
   delete _met_KtResolution;
}

void Ntuplizer::AddHitFitResults()
{
   double   this_ChiSquare;
   double   min_ChiSquare = 10000000.;
   unsigned min_index = -1;
   for( unsigned i = 0; i < _fitResultList.size() ; ++i ){
      this_ChiSquare = _fitResultList[i].chisq() );
      if( this_ChiSquare < min_ChiSquare && this_ChiSquare > 0.0 ){
         min_index = i;
         min_ChiSquare = this_ChiSquare;
      }
   }
   const Fit_Result& best = _fitResultList[min_index];
   math::XYZTLorentzVector  fittedLepW( hitfit::Top_Decaykin::lepw( best.ev() ) ); 
}


void Ntuplizer::AddMET( Lepjets_Event& hitFitEvent, const pat::MET& met )
{
   _met_KtResolution = new Resolution("0,0,12");
   hitFitEventTemplate.met()    = FourVec( met.px() , met.py() , 0 , met.pt() );
   hitFitEventTemplate.kt_res() = *( _met_KtResolution );
   delete _met_KtResolution;
}

void Ntuplizer::AddLepton( Lepjets_Event& hitFitEvent , const pat::Muon& mu )
{
   FourVec lep_p4( mu.px() , mu.py() , mu.pz() , mu.energy() );
   Vector_Resolution lep_resolution = _muonResolution.GetResolution( mu.eta() );
   hitFitEvent.add_lep( lep_p4 , 0 , lep_resolution ); //label = 0 for primary lepton
}

void Ntuplizer::AddLepton( Lepjets_Event& hitFitEvent, const pat::Electron& el )
{
   FourVec lep_p4( el.px() , el.py() , el.pz() , el.energy() );
   Vector_Resolution lep_resolution = _electronResolution.GetResolution( el.eta() );
   hitFitEvent.add_lep( lep_p4 , 0 , lep_resolution ); //label = 0 for primary lepton
}


void Ntuplizer::AddJet( Lepjets_Event& hitFitEvent, const pat::Jet& jet , const int type )
{
   FourVec jetp4( jet.px() , jet.py() , jet.pz(), jet.energy() );
   Vector_Resolution jet_resolution ;
   if( type == hitfit::hadb_label || type == hitfit::lepb_label ){
      jet_resolution = _bJetResolution( jet.eta() );
   } else {
      jet_resolution = _lightJetResolution( jet.eta() );
   }
   hitFitEvent.add_jet( jetp4 , type , jet_resolution );
}

bool Ntuplizer::CheckBTagOrder( const vector<int>& jet_type_list )
{
   //----- First tag must be b tag  -----------------------------------------------
   if( jet_type_list[0] == hitfit::lepb_label ){ return true; }
   if( jet_type_list[0] == hitfit::hadb_label ){ return true; }
   return false;
}

