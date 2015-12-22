/*******************************************************************************
 *
 *  Filename    : HitFitResult.h
 *  Description : Minimal variable to store for HitFit Results
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#ifndef __HITFITRESULT_H__
#define __HITFITRESULT_H__

#include "TLorentzVector.h"

#ifdef CMSSW
#include "TopQuarkAnalysis/TopHitFit/interface/Fit_Result.h"
#endif

class HitFitResult
{
public:
   HitFitResult();
   virtual ~HitFitResult ();

   double TstarMass() const            ;
   double TstarSigma() const           ;
   double ChiSquare() const            ;
   const TLorentzVector& Lepton() const ;
   const TLorentzVector& Neutrino() const ;
   const TLorentzVector& LeptonicW() const ;
   const TLorentzVector& LeptonicTop() const ;
   const TLorentzVector& HadronicW() const ;
   const TLorentzVector& HadronicTop() const ;

#ifdef CMSSW
   void MakeResult(const hitfit::Fit_Result&);
#endif

private:
   double _tstarMass;
   double _tstarSigma;
   double _chiSquare;
   TLorentzVector _lepton;
   TLorentzVector _neutrino;
   TLorentzVector _hadronicW;
   TLorentzVector _hadronicTop;
   TLorentzVector _leptonicW;
   TLorentzVector _leptonicTop;
};

#endif // __HITFITRESULT_H__
