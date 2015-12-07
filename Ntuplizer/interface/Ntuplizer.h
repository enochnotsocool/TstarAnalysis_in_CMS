/*******************************************************************************
 *
 *  Filename    : Ntuplizer.h
 *  Description : Ntuplizer for TstarAnalysis
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
#include "TstarAnalysis/Ntuplizer/interface/LepJets_Event.h"
#include "TstarAnalysis/Ntuplizer/interface/LepJets_Event_Jet.h"
#include "TopQuarkAnalysis/TopHitFit/interface/EtaDepResolution.h"

class Ntuplizer : public BaseAnalyzer {
public:
   explicit Ntuplizer(const edm::ParameterSet&);
   ~Ntuplizer();

protected:
   virtual void addCustomVariables(const edm::Event&);

private:

   //----- TO HIT FIT members  ----------------------------------------------------
   LepJets_Event*     _hitFitEvent;
   Resolution*        _met_KtResolution;
   EtaDepResolution*  _electronResolution;  // Read from external file
   EtaDepResolution*  _muonResolution;      // Read from external file
   EtaDepResolution*  _lightJetResolution;  // Read from external file
   EtaDepResolution*  _bJetResolution;      // Read from external file

   virtual void beginJob() override;
   virtual void endJob() override;

   float ComputeChiSqMass();
   float ComputeEventWeight( const edm::Event& );

   void  AddHitFitResults( const edm::Event& ) ; 
   void  MakeNewEvent();
   void  AddMET( const pat::MET& );
   void  AddLepton( const pat::Muon& );
   void  AddLepton( const pat::Electron& );
   void  AddJet( const pat::Jet& );
};



#endif // __NTUPLIZER_H__
