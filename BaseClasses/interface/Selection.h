/*******************************************************************************
 *
 *  Filename    : Selection.h
 *  Description : Selection functions implementation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Implementation is given in the src directory
 *
*******************************************************************************/
#ifndef __SELECTION_H__
#define __SELECTION_H__

#include "TH1F.h" //For Counting analysis
#include "TstarAnalysis/BaseClasses/interface/TypeDefs.h"

extern bool isGoodPrimaryVertex( const reco::Vertex&, TH1F* = 0 );
extern bool isSelectionMuon( const pat::Muon& , const reco::Vertex& , TH1F* = 0);
extern bool isSelectionElectron( const ElecEDMPtr , const edm::ValueMap<bool>& , TH1F* = 0);
extern bool isVetoMuon( const pat::Muon& , TH1F* = 0);
extern bool isVetoElectron( const ElecEDMPtr , const edm::ValueMap<bool>& , TH1F* = 0);
extern bool isSelectionJet( const pat::Jet& , const MuonList& , const ElectronList& , TH1F* = 0);

#endif // __SELECTION_H__
