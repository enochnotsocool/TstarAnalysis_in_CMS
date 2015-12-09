#include "TstarAnalysis/RootFormat/interface/HitFitBranches.h"

void HitFitBranches::registerVariables( TTree* tree )
{

   tree->Branch( "HitFit.TstarMass", &TstarMass, "HitFit.TstarMass/F" );
   tree->Branch( "HitFit.TstarMassSigma", &TstarMassSigma, "HitFit.TstarMassSigma/F" );
   tree->Branch( "HitFit.ChiSquare", &ChiSquare, "HitFit.ChiSquare/F" );
   tree->Branch( "HitFit.Lepton_Pt", &Lepton_Pt, "HitFit.Lepton_Pt/F" );
   tree->Branch( "HitFit.Lepton_Eta", &Lepton_Eta, "HitFit.Lepton_Eta/F" );
   tree->Branch( "HitFit.Lepton_Phi", &Lepton_Phi, "HitFit.Lepton_Phi/F" );
   tree->Branch( "HitFit.Lepton_Energy", &Lepton_Energy, "HitFit.Lepton_Energy/F" );
   tree->Branch( "HitFit.Neutrino_Pt", &Neutrino_Pt, "HitFit.Neutrino_Pt/F" );
   tree->Branch( "HitFit.Neutrino_Eta", &Neutrino_Eta, "HitFit.Neutrino_Eta/F" );
   tree->Branch( "HitFit.Neutrino_Phi", &Neutrino_Phi, "HitFit.Neutrino_Phi/F" );
   tree->Branch( "HitFit.Neutrino_Energy", &Neutrino_Energy, "HitFit.Neutrino_Energy/F" );
   tree->Branch( "HitFit.Leptonic_W_Pt", &Leptonic_W_Pt, "HitFit.Leptonic_W_Pt/F" );
   tree->Branch( "HitFit.Leptonic_W_Eta", &Leptonic_W_Eta, "HitFit.Leptonic_W_Eta/F" );
   tree->Branch( "HitFit.Leptonic_W_Phi", &Leptonic_W_Phi, "HitFit.Leptonic_W_Phi/F" );
   tree->Branch( "HitFit.Leptonic_W_Energy", &Leptonic_W_Energy, "HitFit.Leptonic_W_Energy/F" );
   tree->Branch( "HitFit.Hadronic_W_Pt", &Hadronic_W_Pt, "HitFit.Hadronic_W_Pt/F" );
   tree->Branch( "HitFit.Hadronic_W_Eta", &Hadronic_W_Eta, "HitFit.Hadronic_W_Eta/F" );
   tree->Branch( "HitFit.Hadronic_W_Phi", &Hadronic_W_Phi, "HitFit.Hadronic_W_Phi/F" );
   tree->Branch( "HitFit.Hadronic_W_Energy", &Hadronic_W_Energy, "HitFit.Hadronic_W_Energy/F" );
   tree->Branch( "HitFit.Leptonic_Top_Pt", &Leptonic_Top_Pt, "HitFit.Leptonic_Top_Pt/F" );
   tree->Branch( "HitFit.Leptonic_Top_Eta", &Leptonic_Top_Eta, "HitFit.Leptonic_Top_Eta/F" );
   tree->Branch( "HitFit.Leptonic_Top_Phi", &Leptonic_Top_Phi, "HitFit.Leptonic_Top_Phi/F" );
   tree->Branch( "HitFit.Leptonic_Top_Energy", &Leptonic_Top_Energy, "HitFit.Leptonic_Top_Energy/F" );
   tree->Branch( "HitFit.Hadronic_Top_Pt", &Hadronic_Top_Pt, "HitFit.Hadronic_Top_Pt/F" );
   tree->Branch( "HitFit.Hadronic_Top_Eta", &Hadronic_Top_Eta, "HitFit.Hadronic_Top_Eta/F" );
   tree->Branch( "HitFit.Hadronic_Top_Phi", &Hadronic_Top_Phi, "HitFit.Hadronic_Top_Phi/F" );
   tree->Branch( "HitFit.Hadronic_Top_Energy", &Hadronic_Top_Energy, "HitFit.Hadronic_Top_Energy/F" );
}

