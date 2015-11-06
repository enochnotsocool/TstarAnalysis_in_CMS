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

class Ntuplizer : public BaseAnalyzer {
public:
   explicit Ntuplizer(const edm::ParameterSet&);
   ~Ntuplizer();

protected:
   virtual void addCustomVariables(const edm::Event&);

private:
   virtual void beginJob() override;
   virtual void endJob() override;

   float computeChiSqMass();
   float computeEventWeight( const edm::Event& );
};



#endif // __NTUPLIZER_H__
