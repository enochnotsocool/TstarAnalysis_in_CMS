/*******************************************************************************
 *
 *  Filename    : HitFitter.cc
 *  Description : Class for communicating with HitFit package
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __HITFITTER_CC__
#define __HITFITTER_CC__

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TstarAnalysis/BaseClasses/interface/TypeDefs.h"

#include "bpkFrameWork/ModifiedHitFit/interface/Lepjets_Event.h"
#include "bpkFrameWork/ModifiedHitFit/interface/Top_Fit.h"

#include "TopQuarkAnalysis/TopHitFit/interface/EtaDepResolution.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Top_Decaykin.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Fit_Result.h"

#include <vector>

class HitFitter
{
public:
   HitFitter( const edm::ParameterSet& );
   virtual ~HitFitter ();

   void setMET( const pat::MET& x ) { _metPtr = &x; }
   void setMuonList( const MuonList& x ) { _muonListPtr = &x ; }
   void setElectronList( const ElectronList& x ){ _elcteoncListPtr = &x; }
   void setBJetList( const JetList& x ) { _btagJetListPtr = &x ; }
   void setLJetList( const JetList& x ) { _lightJetListPtr = &x ; }
   
   const pat::MET&     getMET()          const { return *_metPtr; }
   const MuonList&     getMuonList()     const { return *_muonListPtr; } 
   const ElectronList& getElectronList() const { return *_elcteoncListPtr; }
   const JetList&      getBTagJetList()  const { return *_btagJetListPtr; }
   const JetList&      getLightJetList() const { return *_lightJetListPtr; }

   const std::vector<hitfit::Fit_Result>& getAllResults() const { return _resultList; }
   const hitfit::Fit_Result&              getBestResult() const;

   void  RunPermutations();
   void  ClearAll();

private:
   const pat::MET*      _metPtr; 
   const MuonList*      _muonListPtr;
   const ElectronList*  _elcteoncListPtr;
   const JetList*       _btagJetListPtr;
   const JetList*       _lightJetListPtr;
   std::vector<hitfit::Fit_Result>  _resultList;

   hitfit::Top_Fit*                _top_fitter;
   hitfit::Resolution*             _met_KtResolution;    // Constant for the time being
   hitfit::EtaDepResolution*       _electronResolution;  // Read from external file
   hitfit::EtaDepResolution*       _muonResolution;      // Read from external file
   hitfit::EtaDepResolution*       _lightJetResolution;  // Read from external file
   hitfit::EtaDepResolution*       _bJetResolution;      // Read from external file

   unsigned _debug;
 
   //----- Translator functions  --------------------------------------------------
   void AddHitFitMET( hitfit::Lepjets_Event*, const pat::MET* ) const;
   void AddHitFitLepton( hitfit::Lepjets_Event*, const pat::Muon* ) const;
   void AddHitFitLepton( hitfit::Lepjets_Event*, const reco::GsfElectron* ) const;
   void AddHitFitJet( hitfit::Lepjets_Event*, const pat::Jet* , const int) const;

   //----- B Tag checking functions  ----------------------------------------------
   bool CheckBTagOrder( const std::vector<int>& ) const;
};

#endif // __HITFITTER_CC__
