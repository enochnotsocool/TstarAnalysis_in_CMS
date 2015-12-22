/*******************************************************************************
 *
 *  Filename    : HitFitResult.cc
 *  Description : implementation of minimal hit fit results
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifdef CMSSW
#include "TstarAnalysis/RootFormat/interface/HitFitResult.h"   
#else
#include "HitFitResult.h"
#endif

HitFitResult::HitFitResult(){}
HitFitResult::~HitFitResult(){}

double HitFitResult::TstarMass() const  { return _tstarMass; }
double HitFitResult::TstarSigma() const { return _tstarSigma; }
double HitFitResult::ChiSquare() const  { return _chiSquare; }

const TLorentzVector& HitFitResult::Lepton() const      { return _lepton ; }
const TLorentzVector& HitFitResult::Neutrino() const    { return _neutrino ; }
const TLorentzVector& HitFitResult::LeptonicW() const   { return _leptonicW ; }
const TLorentzVector& HitFitResult::LeptonicTop() const { return _leptonicTop ; }
const TLorentzVector& HitFitResult::HadronicW() const   { return _hadronicW ; }
const TLorentzVector& HitFitResult::HadronicTop() const { return _hadronicTop ; }

