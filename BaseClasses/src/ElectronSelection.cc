/*******************************************************************************
 *
 *  Filename    : ElectronSelection.cc
 *  Description : Election Selection implementation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TH1F.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

typedef edm::Ptr<reco::GsfElectron> ElecEDMPtr;
bool isVetoElectron( const ElecEDMPtr el, const edm::ValueMap<bool>& looseID, TH1F* hist )
{
   if( !looseID[el] ) { return false; }
   if( el->pt() < 15 ) { return false; }
   if( abs(el->eta()) > 2.4 ) { return false; } 
   if( abs(el->eta()) > 1.44 && abs(el->eta()) < 1.57 ){ return false ; }
   return true;
}

bool isSelectionElectron( const ElecEDMPtr el , const edm::ValueMap<bool>& mediumID, TH1F* ) 
{
   if( !mediumID[el] ) { return false; }
   if( el->pt() < 30 ) { return false; }
   if( abs(el->eta()) > 2.1 ) { return false; } 
   if( abs(el->eta()) > 1.44 && abs(el->eta()) < 1.57 ){ return false ; }
   return true;
}

