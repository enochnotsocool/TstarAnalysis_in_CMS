/*******************************************************************************
 *
 *  Filename    : ggChannel_Ntuplizer_ggChannel_Ntuplizer.cc
 *  Description : HitFIt related packages
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/ggChannel_Ntuplizer/interface/ggChannel_Ntuplizer.h"

#include "TopQuarkAnalysis/TopHitFit/interface/Top_Decaykin.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Fit_Result.h"

#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

TLorentzVector ToRootFormat( const hitfit::Fourvec& );

void ggChannel_Ntuplizer::RunHitFit() 
{
   //----- Setting up objects   ---------------------------------------------------
   _hitfitter.setMET( *(_metList.product()->begin()));
   _hitfitter.setMuonList( _selectedMuonList );
   _hitfitter.setElectronList( _selectedElectronList );
   _hitfitter.setBJetList( _selectedBJetList );
   _hitfitter.setLJetList( _selectedLJetList );

   _hitfitter.RunPermutations();

  _event->GetHitFit().MakeResult( _hitfitter.getBestResult() );
}

void HitFitResult::MakeResult( const hitfit::Fit_Result& x )
{
   _tstarMass  = x.mt();
   _tstarSigma = x.sigmt() ;
   _chiSquare  = x.chisq() ;
   _lepton      = ToRootFormat( x.ev().lep(0).p() );
   _neutrino    = ToRootFormat( x.ev().met() );
   _leptonicW   = ToRootFormat( hitfit::Top_Decaykin::lepw( x.ev() ) );
   _leptonicTop = ToRootFormat( hitfit::Top_Decaykin::lept( x.ev() ) );
   _hadronicW   = ToRootFormat( hitfit::Top_Decaykin::hadw( x.ev() ) );
   _hadronicTop = ToRootFormat( hitfit::Top_Decaykin::hadt( x.ev() ) );
}

TLorentzVector ToRootFormat( const hitfit::Fourvec& x )
{
   TLorentzVector ans;
   const math::XYZTLorentzVector y(x);
   ans.SetPtEtaPhiE( y.pt() , y.eta(), y.phi(), y.energy() );
   return ans;
}

