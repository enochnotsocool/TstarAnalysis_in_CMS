/*******************************************************************************
 *
 *  Filename    : ElectronSelection.cc
 *  Description : Selection criteria for electons
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  Details     : 
 *                For implementations of the Cut based IDs, see 
 *                 [1] Twiki       : https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2
 *                 [2] Source Code : https://github.com/cms-analysis/EgammaAnalysis-ElectronTools/blob/master/src/EGammaCutBasedEleId.cc
 *                Selection criteria follow those in:
 *                 [1] TOP-15-005
 *
*******************************************************************************/

#include "TstarAnalysis/Selection/interface/Counting.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

bool isVetoElectron( 
      const reco::GsfElectron& el , 
      const edm::Handle<reco::ConversionCollection>& conversions, 
      const reco::BeamSpot& beamspot,
      const edm::Handle<reco::VertexCollection>& vtxs,
      const double &rho, 
      ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget, 
      TH1F* hist )
{
   HIST_COUNT(0);
   if( !EgammaCutBasedEleId::PassWP(
         EgammaCutBasedEleId::LOOSE,
         el,
         conversions,
         beamspot,
         vtxs,
         el.pfIsolationVariables().sumChargedHadronPt,
         el.pfIsolationVariables().sumPhotonEt,
         el.pfIsolationVariables().sumNeutralHadronEt,
         rho,
         EAtarget) ) { return false; }
   HIST_COUNT(1);
   if( el.pt() < 15 ) { return false; }
   HIST_COUNT(2);
   if( abs(el.eta()) > 2.4 ) { return false; } 
   HIST_COUNT(3);
   if( abs(el.eta()) > 1.44 && abs(el.eta()) < 1.57 ){ return false ; }
   HIST_COUNT(4);
   return true;
}

bool isSelcElectron( 
      const reco::GsfElectron& el , 
      const edm::Handle<reco::ConversionCollection>& conversions, 
      const reco::BeamSpot& beamspot,
      const edm::Handle<reco::VertexCollection>& vtxs,
      const double &rho, 
      ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget , 
      TH1F* hist )
{
   HIST_COUNT(0);
   if( !EgammaCutBasedEleId::PassWP(
         EgammaCutBasedEleId::MEDIUM,
         el,
         conversions,
         beamspot,
         vtxs,
         el.pfIsolationVariables().sumChargedHadronPt,
         el.pfIsolationVariables().sumPhotonEt,
         el.pfIsolationVariables().sumNeutralHadronEt,
         rho,
         EAtarget) ) { return false; }
   HIST_COUNT(1);
   if( el.pt() < 30 ) { return false; }
   HIST_COUNT(2);
   if( abs(el.eta()) > 2.1 ) { return false; } 
   HIST_COUNT(3);
   if( abs(el.eta()) > 1.44 && abs(el.eta()) < 1.57 ){ return false ; }
   HIST_COUNT(4);
   return true;
}
