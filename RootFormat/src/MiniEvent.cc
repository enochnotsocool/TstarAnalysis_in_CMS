/*******************************************************************************
 *
 *  Filename    : MiniEvent.cc
 *  Description : Implementation for mini event class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *  Mainly setting up the storage points in the master tree
 *
*******************************************************************************/
#include "TstarAnalysis/RootFormat/interface/MiniEvent.h"

#include <iostream>
using namespace std;

MiniEvent::MiniEvent() {}
MiniEvent::~MiniEvent(){}

void MiniEvent::registerVariables() 
{
   cout << "Register Variable in MiniEvent"  << endl;;  
   _eventTree->Branch( "chimass" , &_chimass );
   _eventTree->Branch( "IsMuonEvent" , &_isMuon );
   _eventTree->Branch( "IsElectronEvent" , &_isElectron );

   //----- Jet Variables  ---------------------------------------------------------
   _eventTree->Branch( "Number_of_Jets" , & _jet_count );
   _eventTree->Branch( "Jet_Pt"  , &_jet_pt  );
   _eventTree->Branch( "Jet_btag" , &_jet_btag  );
   _eventTree->Branch( "Muon_Pt" , &_muon_pt );
   _eventTree->Branch( "Muon_track_iso" , &_muon_track_iso );
   _eventTree->Branch( "Electron_pt" , &_electron_pt );
}

void MiniEvent::writeVariables()
{
   cout << "Writing Event variables.." << endl;
   _eventTree->Fill();

   //----- Clearing Jet Variable  -------------------------------------------------
   _jet_pt.clear();
   _jet_btag.clear();
   _muon_pt.clear();
   _muon_track_iso.clear();
   _electron_pt.clear();
}

void MiniEvent::readVariables()
{}

//------------------------------------------------------------------------------ 
//   Event information
//------------------------------------------------------------------------------
void MiniEvent::set_chimass( const float x ) { _chimass = x ; }
void MiniEvent::set_jet_count( const unsigned int x ) { _jet_count = x ; }
void MiniEvent::set_isElec( const bool x ){ _isElectron = x; }
void MiniEvent::set_isMuon( const bool x ){ _isMuon = x ; }

bool  MiniEvent::isMuon() { return _isMuon ; }
bool  MiniEvent::isElectron() { return _isElectron; }
float MiniEvent::chimass() { return _chimass; }
unsigned int MiniEvent::jet_count() { return _jet_count; }

void MiniEvent::addJet( const pat::Jet* jet )
{
   _jet_pt.push_back( jet->pt() );
   _jet_btag.push_back( jet->bDiscriminator("pfCombinedSecondaryVertexV2BJetTags" ) );
}

void MiniEvent::addMuon( const pat::Muon* mu )
{
   _muon_pt.push_back( mu->pt() );
   _muon_track_iso.push_back( mu->trackIso() / mu->pt() );
}

void MiniEvent::addElectron( const reco::GsfElectron* el )
{
   _electron_pt.push_back( el->pt() );
}
