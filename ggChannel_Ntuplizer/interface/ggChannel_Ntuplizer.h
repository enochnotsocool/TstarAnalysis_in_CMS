/*******************************************************************************
 *
 *  Filename    : ggChannel_Ntuplizer.h
 *  Description : ggChannel_Ntuplizer for TstarAnalysis
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
#include "TstarAnalysis/ggChannel_Ntuplizer/interface/HitFitter.h"

#include <vector>

class ggChannel_Ntuplizer : public BaseAnalyzer {
public:
   explicit ggChannel_Ntuplizer(const edm::ParameterSet&);
   ~ggChannel_Ntuplizer();

protected:
   virtual void addCustomVariables(const edm::Event&);

private:

   HitFitter      _hitfitter;
   HitFitBranches _hitfitBranches; 

   //----- Inherited member functions  --------------------------------------------
   virtual void beginJob() override;
   virtual void endJob() override;

   //------------------------------------------------------------------------------ 
   //   Analysis specific member functions
   //------------------------------------------------------------------------------
   float ComputeChiSqMass();
   float ComputeEventWeight( const edm::Event& );

   void RunHitFit();
};



#endif // __NTUPLIZER_H__
