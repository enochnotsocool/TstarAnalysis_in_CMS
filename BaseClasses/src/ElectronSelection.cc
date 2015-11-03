/*******************************************************************************
 *
 *  Filename    : ElectronSelection.cc
 *  Description : Election Selection implementation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TH1F.h"
#include "TstarAnalysis/BaseClasses/interface/TypeDefs.h"
#include "TstarAnalysis/BaseClasses/interface/Limits.h"

bool isVetoElectron( const ElecEDMPtr el, const edm::ValueMap<bool>& looseID, TH1F* hist )
{
   if( hist!=NULL) { hist->Fill(0); }
   if( !looseID[el] ) { return false; }
   if( hist!=NULL) { hist->Fill(1); }
   if( el->pt() < VETO_ELEC_PT_LIM ) { return false; }
   if( hist!=NULL) { hist->Fill(2); }
   if( abs(el->eta()) > VETO_ELEC_ETA_LIM ) { return false; } 
   if( hist!=NULL) { hist->Fill(3); }
   if( abs(el->eta()) > 1.44 && abs(el->eta()) < 1.57 ){ return false ; }
   if( hist!=NULL) { hist->Fill(4); }
   return true;
}

bool isSelectionElectron( const ElecEDMPtr el , const edm::ValueMap<bool>& mediumID, TH1F* hist ) 
{
   if( hist!=NULL) { hist->Fill(0); }
   if( !mediumID[el] ) { return false; }
   if( hist!=NULL) { hist->Fill(1); }
   if( el->pt() < SELECTED_ELEC_PT_LIM ) { return false; }
   if( hist!=NULL) { hist->Fill(2); }
   if( abs(el->eta()) > SELECTED_ELEC_ETA_LIM ) { return false; } 
   if( hist!=NULL) { hist->Fill(3); }
   if( abs(el->eta()) > 1.44 && abs(el->eta()) < 1.57 ){ return false ; }
   if( hist!=NULL) { hist->Fill(4); }
   return true;
}

