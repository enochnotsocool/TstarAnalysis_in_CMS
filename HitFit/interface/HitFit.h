/*******************************************************************************
 *
 *  Filename    : HitFit.h
 *  Description : HitFit for TstarAnalysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : 
 *  This is an attempt to extract all event based variables from the mini
 *  AOD format, including uncertainties
 *
*******************************************************************************/
#ifndef __NTUPLIZER_H__
#define __NTUPLIZER_H__

#include "TstarAnalysis/BaseClasses/interface/BaseAnalyzer.h"
#include "TstarAnalysis/RootFormat/interface/HitFitBranches.h"
#include "bpkFrameWork/ModifiedHitFit/interface/Lepjets_Event.h"
#include "bpkFrameWork/ModifiedHitFit/interface/Lepjets_Event_Jet.h"
#include "bpkFrameWork/ModifiedHitFit/interface/Top_Fit.h"
#include "TopQuarkAnalysis/TopHitFit/interface/EtaDepResolution.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Fit_Result.h"

#include <vector>

class HitFit : public BaseAnalyzer {
public:
   explicit HitFit(const edm::ParameterSet&);
   ~HitFit();

protected:
   virtual void addCustomVariables(const edm::Event&);

private:

   //----- Top HIT FIT data members  ----------------------------------------------
   hitfit::Top_Fit*                _top_fitter;
   hitfit::Resolution*             _met_KtResolution;    // Constant for the time being
   hitfit::EtaDepResolution*       _electronResolution;  // Read from external file
   hitfit::EtaDepResolution*       _muonResolution;      // Read from external file
   hitfit::EtaDepResolution*       _lightJetResolution;  // Read from external file
   hitfit::EtaDepResolution*       _bJetResolution;      // Read from external file
   std::vector<hitfit::Fit_Result> _fitResultList;

   HitFitBranches _hitfitBranches; 

   //----- Inherited member functions  --------------------------------------------
   virtual void beginJob() override;
   virtual void endJob() override;

   //------------------------------------------------------------------------------ 
   //   Analysis specific member functions
   //------------------------------------------------------------------------------
   float ComputeChiSqMass();
   float ComputeEventWeight( const edm::Event& );

   //----- HIT FIT related member functions  --------------------------------------
   void  InitHitFit( const edm::ParameterSet& ); //Constructor for analysis wide variable
   void  ClearHitFit();
   void  RunHitFit( const edm::Event& ) ; 
   void  MakeNewEvent();
   void  AddMET( hitfit::Lepjets_Event& , const pat::MET& );
   void  AddLepton( hitfit::Lepjets_Event&, const pat::Muon& );
   void  AddLepton( hitfit::Lepjets_Event&, const pat::Electron& );
   void  AddJet( hitfit::Lepjets_Event&, const pat::Jet& , const int );
   bool  CheckBTagOrder( const std::vector<int>& );
   void  AddHitFitResults();
};



#endif // __NTUPLIZER_H__
