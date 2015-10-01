#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

extern bool isGoodPV( const reco::Vertex& ) ;
extern bool isVetoMuon( const pat::Muon& ) ;
extern bool isSelcMuon( const pat::Muon& ) ;
extern bool isSelcJet( const pat::Jet& ) ;

extern bool isVetoElectron( 
      const reco::GsfElectron& , 
      const edm::Handle<reco::ConversionCollection>& conversions, 
      const reco::BeamSpot& beamspot,
      const edm::Handle<reco::VertexCollection>& vtxs,
      const double &rho, 
      ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget);

extern bool isSelcElectron( 
      const reco::GsfElectron& , 
      const edm::Handle<reco::ConversionCollection>& conversions, 
      const reco::BeamSpot& beamspot,
      const edm::Handle<reco::VertexCollection>& vtxs,
      const double &rho, 
      ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget);


