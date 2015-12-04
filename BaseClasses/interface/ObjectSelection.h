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

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TstarAnalysis/BaseClasses/interface/TypeDefs.h"

class ObjectSelection
{
public:
   ObjectSelection( const edm::ParameterSet& );
   virtual ~ObjectSelection ();

   bool isGoodPrimaryVertex( const reco::Vertex&, TH1F* = 0 ) const ;
   bool isSelectionMuon( const pat::Muon& , const reco::Vertex& , TH1F* = 0) const ;
   bool isSelectionElectron( const ElecEDMPtr , const edm::ValueMap<bool>& , TH1F* = 0) const ;
   bool isVetoMuon( const pat::Muon& , TH1F* = 0) const;
   bool isVetoElectron( const ElecEDMPtr , const edm::ValueMap<bool>& , TH1F* = 0) const;
   bool isSelectionJet( const pat::Jet& , const MuonList& , const ElectronList& , TH1F* = 0) const;

private:

   //----- Vertex Selection parameters  -------------------------------------------
   const double fVertex_Minimum_DegreeOfFreedom;
   const double fVertex_Maximum_Z;
   const double fVertex_Maximum_Rho;

   //----- Muon Selection parameters  ---------------------------------------------
   const double fMuon_Minimum_Pt;
   const double fMuon_Maximum_Eta;
   const double fMuon_Maximum_Isolation;
   const double fMuon_Veto_Minimum_Pt;
   const double fMuon_Veto_Maximum_Eta;
   const double fMuon_Veto_Maximum_Isolation;
  
   //----- Electron selection parameters  -----------------------------------------
   const double fElectron_Minimum_Pt;
   const double fElectron_Maximum_Eta;
   const double fElectron_Veto_Minimum_Pt;
   const double fElectron_Veto_Maximum_Eta;
   const double fElectron_Mininum_CrackEta;
   const double fElectron_Maximum_CrackEta;

   //----- Jet Selection parameters  ----------------------------------------------
   const double fJet_Minimum_Pt;
   const double fJet_Maximum_Eta;
   const double fJet_Minimum_DeltaR;
};

#endif // __SELECTION_H__
