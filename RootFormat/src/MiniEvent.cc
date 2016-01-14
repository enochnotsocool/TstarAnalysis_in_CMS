/*******************************************************************************
 *
 *  Filename    : MiniEvent.cc
 *  Description : Implementation of minimal event for Tstar analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifdef CMSSW
#include "TstarAnalysis/RootFormat/interface/MiniEvent.h"
#else
#include "MiniEvent.h"
#endif

MiniEvent::MiniEvent(){}
MiniEvent::~MiniEvent(){}

//------------------------------------------------------------------------------ 
//   Event ID Members
//------------------------------------------------------------------------------
void MiniEvent::SetRunNumber( const unsigned x ){ _runNumber = x ; }
void MiniEvent::SetLumiNumber( const unsigned long long x ) { _lumiNumber = x; }
void MiniEvent::SetEventNumber( const unsigned x ) { _eventNumber = x ; }
void MiniEvent::SetBunchCrossing( const unsigned x ) { _bunchCrossingNumber = x ; }
unsigned MiniEvent::RunNumber() const { return _runNumber; }
unsigned MiniEvent::EventNumber() const { return _eventNumber; }
unsigned MiniEvent::BunchCrossing() const { return _bunchCrossingNumber; }
unsigned long long MiniEvent::LumiNumber() const { return _lumiNumber; }


//------------------------------------------------------------------------------ 
//   MET Functions
//------------------------------------------------------------------------------
void MiniEvent::SetMet( const double met , const double phi )
{ 
   _met  = met ; _metphi = phi; 
}
double MiniEvent::MET() const { return _met ; }
double MiniEvent::METPhi() const { return _metphi; }

//------------------------------------------------------------------------------ 
//   Weighting Functions
//------------------------------------------------------------------------------
void MiniEvent::SetPileUp( const unsigned x ) {  _pileup = x ; }
unsigned MiniEvent::PileUp() const { return _pileup; }

double MiniEvent::TotalEventWeight() const { return _totalEventWeight; }
void MiniEvent::SetTotalWeight(const double x){ _totalEventWeight = x ; }

//------------------------------------------------------------------------------ 
//   Particle List Member functions
//------------------------------------------------------------------------------
void MiniEvent::ClearLists() 
{
   _jetList.clear();
   _muonList.clear();
   _electronList.clear();
}

std::vector<MiniJet>&      MiniEvent::JetList()      { return _jetList; }
std::vector<MiniMuon>&     MiniEvent::MuonList()     { return _muonList; }
std::vector<MiniElectron>& MiniEvent::ElectronList() { return _electronList; }
ChiSquareResult&  MiniEvent::GetChiSquare() { return _chisqresult; }
HitFitResult&     MiniEvent::GetHitFit()    { return _hitfitresult; }

void MiniEvent::AddJet( const MiniJet& x ) { _jetList.push_back( x ); }
void MiniEvent::AddMuon( const MiniMuon& x ) { _muonList.push_back( x ); }
void MiniEvent::AddElectron( const MiniElectron& x ) { _electronList.push_back( x ); }


