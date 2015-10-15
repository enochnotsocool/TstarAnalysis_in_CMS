/*******************************************************************************
 *
 *  Filename    : MiniEvent.h
 *  Description : Variables stored for a mini event
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef __MINIEVENT_H__
#define __MINIEVENT_H__

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include <vector>
#include "TLorentzVector.h"
#include "TTree.h"

class MiniEvent {
public:
   MiniEvent();
   virtual ~MiniEvent ();

   void registerVariables();
   void writeVariables();
   void readVariables();

   void  set_chimass( const float );
   void  set_jet_count( const unsigned int );
   void  set_isMuon( const bool );
   void  set_isElec( const bool );
   bool  isMuon();
   bool  isElectron();
   float chimass();
   unsigned int jet_count();

   void addJet( const pat::Jet* );
   void addMuon( const pat::Muon* );
   void addElectron( const reco::GsfElectron* ); 

   TTree*  _eventTree;
private:

   bool    _isMuon;
   bool    _isElectron;
   float   _chimass;

   //----- Jet Variables  ---------------------------------------------------------
   unsigned int _jet_count;
   std::vector<float> _jet_pt;
   std::vector<float> _jet_btag;

   //----- Muon Variables  --------------------------------------------------------
   std::vector<float> _muon_track_iso;
   std::vector<float> _muon_pt;

   //----- Electron variables  ----------------------------------------------------
   std::vector<float> _electron_pt;
};

#endif // __MINIEVENT_H__
