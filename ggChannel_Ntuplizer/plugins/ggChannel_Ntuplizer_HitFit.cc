/*******************************************************************************
 *
 *  Filename    : ggChannel_Ntuplizer_ggChannel_Ntuplizer.cc
 *  Description : HitFIt related packages
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/ggChannel_Ntuplizer/interface/ggChannel_Ntuplizer.h"

#include "TopQuarkAnalysis/TopHitFit/interface/fourvec.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Top_Decaykin.h"
#include "TopQuarkAnalysis/TopHitFit/interface/Defaults_Text.h"

#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

void ggChannel_Ntuplizer::RunHitFit() 
{
   //----- Setting up objects   ---------------------------------------------------
   _hitfitter.setMET( *(_metList.product()->begin()));
   _hitfitter.setMuonList( _selectedMuonList );
   _hitfitter.setElectronList( _selectedElectronList );
   _hitfitter.setBJetList( _selectedBJetList );
   _hitfitter.setLJetList( _selectedLJetList );

   _hitfitter.RunPermutations();

   const Fit_Result& best = _hitfitter.getBestResult();
   const math::XYZTLorentzVector fittedLepton( best.ev().lep(0).p() );
   const math::XYZTLorentzVector fittedNeutrino( best.ev().met() );
   const math::XYZTLorentzVector fittedKt    ( best.ev().kt() );
   const math::XYZTLorentzVector fittedLepW  ( hitfit::Top_Decaykin::lepw( best.ev() ) );
   const math::XYZTLorentzVector fittedLepTop( hitfit::Top_Decaykin::lept( best.ev() ) );
   const math::XYZTLorentzVector fittedHadW  ( hitfit::Top_Decaykin::hadw( best.ev() ) );
   const math::XYZTLorentzVector fittedHadTop( hitfit::Top_Decaykin::hadt( best.ev() ) );

   _hitfitBranches.TstarMass      = best.mt();
   _hitfitBranches.TstarMassSigma = best.sigmt();
   _hitfitBranches.ChiSquare      = best.chisq();

   _hitfitBranches.Lepton_Pt     = fittedLepton.pt();
   _hitfitBranches.Lepton_Eta    = fittedLepton.eta();
   _hitfitBranches.Lepton_Phi    = fittedLepton.phi();
   _hitfitBranches.Lepton_Energy = fittedLepton.energy();
   _hitfitBranches.Lepton_Mass   = fittedLepton.mass();
   
   _hitfitBranches.Neutrino_Pt     = fittedNeutrino.pt() ;
   _hitfitBranches.Neutrino_Eta    = fittedNeutrino.eta();
   _hitfitBranches.Neutrino_Phi    = fittedNeutrino.phi();
   _hitfitBranches.Neutrino_Energy = fittedNeutrino.energy();
   _hitfitBranches.Neutrino_Mass   = fittedNeutrino.mass();

   _hitfitBranches.Leptonic_W_Pt     = fittedLepW.pt();       
   _hitfitBranches.Leptonic_W_Eta    = fittedLepW.eta();       
   _hitfitBranches.Leptonic_W_Phi    = fittedLepW.phi();       
   _hitfitBranches.Leptonic_W_Energy = fittedLepW.energy();
   _hitfitBranches.Leptonic_W_Mass   = fittedLepW.mass();
   _hitfitBranches.Hadronic_W_Pt     = fittedHadW.pt();
   _hitfitBranches.Hadronic_W_Eta    = fittedHadW.eta();
   _hitfitBranches.Hadronic_W_Phi    = fittedHadW.phi();
   _hitfitBranches.Hadronic_W_Energy = fittedHadW.energy();
   _hitfitBranches.Hadronic_W_Mass   = fittedHadW.mass();

   _hitfitBranches.Leptonic_Top_Pt      = fittedLepTop.pt();
   _hitfitBranches.Leptonic_Top_Eta     = fittedLepTop.eta();
   _hitfitBranches.Leptonic_Top_Phi     = fittedLepTop.phi();
   _hitfitBranches.Leptonic_Top_Energy  = fittedLepTop.energy();
   _hitfitBranches.Leptonic_Top_Mass    = fittedLepTop.mass();
   _hitfitBranches.Hadronic_Top_Pt      = fittedHadTop.pt() ;
   _hitfitBranches.Hadronic_Top_Eta     = fittedHadTop.eta() ;
   _hitfitBranches.Hadronic_Top_Phi     = fittedHadTop.phi() ;
   _hitfitBranches.Hadronic_Top_Energy  = fittedHadTop.energy() ;
   _hitfitBranches.Hadronic_Top_Mass    = fittedHadTop.mass();

   _hitfitter.ClearAll();
}
