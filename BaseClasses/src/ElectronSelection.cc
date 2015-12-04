/*******************************************************************************
 *
 *  Filename    : ElectronSelection.cc
 *  Description : Election Selection implementation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TH1F.h"
#include "TstarAnalysis/BaseClasses/interface/Utils.h"
#include "TstarAnalysis/BaseClasses/interface/ObjectSelection.h"

bool ObjectSelection::isVetoElectron( const ElecEDMPtr el, const edm::ValueMap<bool>& looseID, TH1F* hist ) const
{
   int i = 0 ;
   FillHistAtBin( hist , i );
   if( !looseID[el] ) { return false; }
   FillHistAtBin( hist , i );
   if( el->pt() < fElectron_Veto_Minimum_Pt ) { return false; }
   FillHistAtBin( hist , i );
   if( abs(el->eta()) > fElectron_Veto_Maximum_Eta ) { return false; } 
   FillHistAtBin( hist , i );
   if( abs(el->eta()) > fElectron_Mininum_CrackEta && 
       abs(el->eta()) < fElectron_Maximum_CrackEta   ){ return false ; }
   FillHistAtBin( hist , i );
   return true;
}

bool ObjectSelection::isSelectionElectron( const ElecEDMPtr el , const edm::ValueMap<bool>& mediumID, TH1F* hist ) const
{
   int i = 0 ;
   FillHistAtBin( hist , i );
   if( !mediumID[el] ) { return false; }
   FillHistAtBin( hist , i );
   if( el->pt() < fElectron_Minimum_Pt ) { return false; }
   FillHistAtBin( hist , i );
   if( abs(el->eta()) > fElectron_Maximum_Eta ) { return false; } 
   FillHistAtBin( hist , i );
   if( abs(el->eta()) > fElectron_Mininum_CrackEta && 
       abs(el->eta()) < fElectron_Maximum_CrackEta ){ return false ; }
   FillHistAtBin( hist , i );
   return true;
}

