#include "TstarAnalysis/RootFormat/interface/MiniEvent.h"

MiniEvent::MiniEvent(){}
MiniEvent::~MiniEvent(){}

void MiniEvent::ClearLists() 
{
   _jetList.clear();
   _muonList.clear();
   _electronList.clear();
}

std::vector<MiniJet>&      MiniEvent::JetList()      { return _jetList; }
std::vector<MiniMuon>&     MiniEvent::MuonList()     { return _muonList; }
std::vector<MiniElectron>& MiniEvent::ElectronList() { return _electronList; }

void MiniEvent::AddJet( const MiniJet& x ) { _jetList.push_back( x ); }
void MiniEvent::AddMuon( const MiniMuon& x ) { _muonList.push_back( x ); }
void MiniEvent::AddElectron( const MiniElectron& x ) { _electronList.push_back( x ); }

void MiniEvent::SetMet( const double met , const double phi )
{ 
   _met  = met ; _metphi = phi; 
}
double MiniEvent::MET() const { return _met ; }
double MiniEvent::METPhi() const { return _metphi; }

void MiniEvent::SetPileUp( const unsigned x ) {  _pileup = x ; }
unsigned MiniEvent::PileUp() const { return _pileup; }


