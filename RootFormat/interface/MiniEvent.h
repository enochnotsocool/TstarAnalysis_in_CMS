/*******************************************************************************
 *
 *  Filename    : MiniEvent.h
 *  Description : Minimal implementation of event for combine analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 * 
 *
*******************************************************************************/

#ifndef __MINIEVENT_H__
#define __MINIEVENT_H__

#include <vector>

#ifdef CMSSW
#include "TstarAnalysis/RootFormat/interface/MiniJet.h"
#include "TstarAnalysis/RootFormat/interface/MiniMuon.h"
#include "TstarAnalysis/RootFormat/interface/MiniElectron.h"
#else
#include "MiniJet.h"
#include "MiniMuon.h"
#include "MiniElectron.h"
#endif

class MiniEvent 
{
public:
   MiniEvent();
   virtual ~MiniEvent ();

   void SetRunNumber( const unsigned );
   void SetLumiNumber( const unsigned long long );
   void SetEventNumber( const unsigned );
   void SetBunchCrossing( const unsigned );
   unsigned RunNumber() const ;
   unsigned EventNumber() const;
   unsigned BunchCrossing() const;
   unsigned long long LumiNumber() const;

   void     SetPileUp( const unsigned );
   unsigned PileUp() const;
   void     SetTotalWeight( const double );
   double   TotalEventWeight() const;
   
   void   SetMet( const double, const double );
   double MET() const;
   double METPhi() const;

   std::vector<MiniJet>&  JetList();
   std::vector<MiniMuon>& MuonList() ;
   std::vector<MiniElectron>& ElectronList();
   void AddJet( const MiniJet& );
   void AddMuon( const MiniMuon& );
   void AddElectron( const MiniElectron& );
   void ClearLists();
   
private:
   //----- Event id number  -------------------------------------------------------
   unsigned            _runNumber;
   unsigned long long  _lumiNumber;
   unsigned            _eventNumber;
   unsigned            _bunchCrossingNumber;
   
   unsigned _pileup;
   double   _totalEventWeight;
   double _met;
   double _metphi;

   //----- LCD dictionary generation doesn't play well with const  ----------------
   std::vector<MiniJet>      _jetList;
   std::vector<MiniMuon>     _muonList;
   std::vector<MiniElectron> _electronList;
};

#endif // __MINIEVENT_H__
