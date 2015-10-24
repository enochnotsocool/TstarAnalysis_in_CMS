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
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

typedef std::vector<const reco::GsfElectron*> ElecList;
typedef std::vector<const pat::Muon*> MuonList; 
typedef edm::Ptr<reco::GsfElectron> ElecEDMPtr;

extern bool isGoodPrimaryVertex( const reco::Vertex&, TH1F* );
extern bool isSelectionMuon( const pat::Muon& , const reco::Vertex& , TH1F* );
extern bool isSelectionElectron( const ElecEDMPtr , const edm::ValueMap<bool>& , TH1F* );
extern bool isVetoMuon( const pat::Muon& , TH1F* );
extern bool isVetoElectron( const ElecEDMPtr , const edm::ValueMap<bool>& , TH1F* );
extern bool isSelectionJet( const pat::Jet& , const MuonList& , const ElectronList& , TH1F* );

#endif // __SELECTION_H__
