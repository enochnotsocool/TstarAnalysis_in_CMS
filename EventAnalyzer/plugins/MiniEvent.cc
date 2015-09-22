/***************************************************************************************************
 *
 *  Filename    : MiniEvent.cc
 *  Description : Implementation for MiniEvent Class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : The Key component for this class is the particle and event cleaning algorithms
 *                This algorithms will be implemented directly in the constructor with helper 
 *                functions.
 *
***************************************************************************************************/

#include "TstarAnalysis/EventAnalyzer/interface/MiniEvent.h"

//-------------------------------------------------------------------------------------------------- 
//   Constructor and destructor
//-------------------------------------------------------------------------------------------------- 
MiniEvent::MiniEvent() {};
MiniEvent::~MiniEvent() {};


//-------------------------------------------------------------------------------------------------- 
//   Member access methods
//-------------------------------------------------------------------------------------------------- 
const std::vector<pat::Jet>&      MiniEvent::jetList()      const { return _jetList      ; }
const std::vector<pat::Muon>&     MiniEvent::muonList()     const { return _muonList     ; }
const std::vector<pat::Electron>& MiniEvent::electronList() const { return _electronList ; }
const std::vector<pat::Photon>&   MiniEvent::photonList()   const { return _photonList   ; }
const std::vector<pat::MET>&      MiniEvent::metList()      const { return _metList      ; }

ULong64_t MiniEvent::runNumber()   const { return _runNumber  ; }
ULong64_t MiniEvent::eventNumber() const { return _eventNumber; }
ULong64_t MiniEvent::lumiNumber()  const { return _lumiNumber ; }

