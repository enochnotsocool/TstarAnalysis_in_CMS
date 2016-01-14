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

#include "TstarAnalysis/ggChannel_Ntuplizer/interface/HitFitter.h"
#include "TstarAnalysis/ggChannel_Ntuplizer/interface/ChiSquareSolver.h"
#include "TstarAnalysis/RootFormat/interface/ChiSquareResult.h"
#include "TstarAnalysis/RootFormat/interface/HitFitResult.h"
#include <vector>

class ggChannel_Ntuplizer : public BaseAnalyzer {
public:
   explicit ggChannel_Ntuplizer(const edm::ParameterSet&);
   ~ggChannel_Ntuplizer();

protected:
   virtual void addCustomVariables(const edm::Event&);

private:
   ChiSquareSolver  _chisqSolver;

   HitFitter     _hitfitter;

   // Flags of operation 
   const bool  _runChiSq;
   const bool _runHitFit;

   //----- Inherited member functions  --------------------------------------------
   virtual void beginJob() override;
   virtual void endJob() override;

   //------------------------------------------------------------------------------ 
   //   Analysis specific member functions
   //------------------------------------------------------------------------------
   float ComputeEventWeight( const edm::Event& );

   void RunChiSquare();
   void RunHitFit();
};



#endif // __NTUPLIZER_H__
