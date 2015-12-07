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

void Ntuplizer::AddHitFitResults() 
{
   _hitFitEvent = new _hitFitEvent( 0,0 );

   //----- Setting up MET  --------------------------------------------------------
   const auto& met = (*(_metList.product()))->begin();   
   _met_KtResolution = new Resolution("0,0,12");
   _hitFitEvent->met()    = FourVec( met.px() , met.py() , 0 , met.pt() );
   _hitFitEvent->kt_res() = *( _met_KtResolution );

   //----- Setting up Leptons  ----------------------------------------------------
   for( const auto& muon : _selectedMuonList ){
      AddLepton( *muon );
   }
   for( const auto& elec : _selectedElectronList ){
      AddLepton( *elec );
   }

   delete _met_KtResolution;
   delete _hitFitEvent;
}

void Ntuplizer::AddLepton( const pat::Muon& mu )
{
   FourVec lep_p4( mu.px() , mu.py() , mu.pz() , mu.energy() );
   Vector_Resolution lep_resolution = _muonResolution.GetResolution( mu.eta() );
   _hitFitEvent->add_lep( lep_p4 , 0 , lep_resolution ); //label = 0 for primary lepton
}

void Ntuplizer::AddLepton( const pat::Electron& )
{
   FourVec lep_p4( mu.px() , mu.py() , mu.pz() , mu.energy() );
   Vector_Resolution lep_resolution = _electronResolution.GetResolution( mu.eta() );
   _hitFitEvent->add_lep( lep_p4 , 0 , lep_resolution ); //label = 0 for primary lepton
}


void Ntuplizer::AddJet( const pat::Jet& )
{

}
