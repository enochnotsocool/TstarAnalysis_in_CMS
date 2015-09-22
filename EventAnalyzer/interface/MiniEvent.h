/***************************************************************************************************
 *
 *  Filename    : MiniEvent.h
 *  Description : Using a custom Event Class for ease of acces
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : Here, we will only be storing the objects of interest in a std::vector
 *
***************************************************************************************************/
#ifndef __MINIEVENT_H__
#define __MINIEVENT_H__

#include <vector>
//-------------------------------------------------------------------------------------------------- 
//   CMSSW Libraries
//-------------------------------------------------------------------------------------------------- 
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"

class MiniEvent {
public:
   MiniEvent ();
   virtual ~MiniEvent ();
   // Data Member access functions
   const std::vector<pat::Jet>&      jetList()      const ;
   const std::vector<pat::Muon>&     muonList()     const ;
   const std::vector<pat::Electron>& electronList() const ;
   const std::vector<pat::Photon>&   photonList()   const ;
   const std::vector<pat::MET>&      metList()      const ;

   ULong64_t runNumber()   const ;
   ULong64_t eventNumber() const ;
   ULong64_t lumiNumber()  const ; 


private:
   // Physical object list
   std::vector<pat::Jet>      _jetList;
   std::vector<pat::Muon>     _muonList;
   std::vector<pat::Electron> _electronList;
   std::vector<pat::Photon>   _photonList;
   std::vector<pat::MET>      _metList;

   // Event specific objects list
   ULong64_t _runNumber;
   ULong64_t _eventNumber;
   ULong64_t _lumiNumber;
};

#endif // __MINIEVENT_H__

