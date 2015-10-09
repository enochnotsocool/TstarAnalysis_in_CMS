/*******************************************************************************
 *
 *  Filename    : Selection.h
 *  Description : A list of selection function
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : Functions here could be used for any on of the plugins
 *                For the definition/implementation of the functions, 
 *                read the files in Selection/src/
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

extern bool isGoodPV( const reco::Vertex& , TH1F* = 0 ) ;
extern bool isVetoMuon( const pat::Muon& , TH1F* = 0 ) ;
extern bool isSelcMuon( const pat::Muon& , const reco::Vertex& , TH1F* = 0 ) ;
extern bool isSelcJet( const pat::Jet& , const ElecList& ,const MuonList& , TH1F* = 0 , float pt_limit=50.0 ) ;

extern bool isVetoElectron( 
      const reco::GsfElectron& , 
      const edm::Handle<reco::ConversionCollection>& conversions, 
      const reco::BeamSpot& beamspot,
      const edm::Handle<reco::VertexCollection>& vtxs,
      const double &rho, 
      ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget,
      TH1F* = 0 );

extern bool isSelcElectron( 
      const reco::GsfElectron& , 
      const edm::Handle<reco::ConversionCollection>& conversions, 
      const reco::BeamSpot& beamspot,
      const edm::Handle<reco::VertexCollection>& vtxs,
      const double &rho, 
      ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget,
      TH1F* = 0 );

#endif // __SELECTION_H__

