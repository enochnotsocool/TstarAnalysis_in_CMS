#include "HitFitBranches.h"

void HitFitBranches::retrieveVariables( TTree* tree )
{

   tree->SetBranchAddress( "HitFit.TstarMass", &TstarMass );
   tree->SetBranchAddress( "HitFit.TstarMassSigma", &TstarMassSigma );
   tree->SetBranchAddress( "HitFit.ChiSquare", &ChiSquare );
   tree->SetBranchAddress( "HitFit.Lepton_Pt", &Lepton_Pt );
   tree->SetBranchAddress( "HitFit.Lepton_Eta", &Lepton_Eta );
   tree->SetBranchAddress( "HitFit.Lepton_Phi", &Lepton_Phi );
   tree->SetBranchAddress( "HitFit.Lepton_Energy", &Lepton_Energy );
   tree->SetBranchAddress( "HitFit.Lepton_Mass", &Lepton_Mass );
   tree->SetBranchAddress( "HitFit.Neutrino_Pt", &Neutrino_Pt );
   tree->SetBranchAddress( "HitFit.Neutrino_Eta", &Neutrino_Eta );
   tree->SetBranchAddress( "HitFit.Neutrino_Phi", &Neutrino_Phi );
   tree->SetBranchAddress( "HitFit.Neutrino_Energy", &Neutrino_Energy );
   tree->SetBranchAddress( "HitFit.Neutrino_Mass", &Neutrino_Mass );
   tree->SetBranchAddress( "HitFit.Leptonic_W_Pt", &Leptonic_W_Pt );
   tree->SetBranchAddress( "HitFit.Leptonic_W_Eta", &Leptonic_W_Eta );
   tree->SetBranchAddress( "HitFit.Leptonic_W_Phi", &Leptonic_W_Phi );
   tree->SetBranchAddress( "HitFit.Leptonic_W_Energy", &Leptonic_W_Energy );
   tree->SetBranchAddress( "HitFit.Leptonic_W_Mass", &Leptonic_W_Mass );
   tree->SetBranchAddress( "HitFit.Hadronic_W_Pt", &Hadronic_W_Pt );
   tree->SetBranchAddress( "HitFit.Hadronic_W_Eta", &Hadronic_W_Eta );
   tree->SetBranchAddress( "HitFit.Hadronic_W_Phi", &Hadronic_W_Phi );
   tree->SetBranchAddress( "HitFit.Hadronic_W_Energy", &Hadronic_W_Energy );
   tree->SetBranchAddress( "HitFit.Hadronic_W_Mass", &Hadronic_W_Mass );
   tree->SetBranchAddress( "HitFit.Leptonic_Top_Pt", &Leptonic_Top_Pt );
   tree->SetBranchAddress( "HitFit.Leptonic_Top_Eta", &Leptonic_Top_Eta );
   tree->SetBranchAddress( "HitFit.Leptonic_Top_Phi", &Leptonic_Top_Phi );
   tree->SetBranchAddress( "HitFit.Leptonic_Top_Energy", &Leptonic_Top_Energy );
   tree->SetBranchAddress( "HitFit.Leptonic_Top_Mass", &Leptonic_Top_Mass );
   tree->SetBranchAddress( "HitFit.Hadronic_Top_Pt", &Hadronic_Top_Pt );
   tree->SetBranchAddress( "HitFit.Hadronic_Top_Eta", &Hadronic_Top_Eta );
   tree->SetBranchAddress( "HitFit.Hadronic_Top_Phi", &Hadronic_Top_Phi );
   tree->SetBranchAddress( "HitFit.Hadronic_Top_Energy", &Hadronic_Top_Energy );
   tree->SetBranchAddress( "HitFit.Hadronic_Top_Mass", &Hadronic_Top_Mass );
}


