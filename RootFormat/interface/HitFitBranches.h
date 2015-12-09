#ifndef __HitFitBRANCHES_H__
#define __HitFitBRANCHES_H__

#include "TTree.h"
#define MAX_OBJS 128

class HitFitBranches {
public:
   HitFitBranches() {}
   virtual ~HitFitBranches () {}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );

   Float_t    TstarMass;
   Float_t    TstarMassSigma;
   Float_t    ChiSquare;
   Float_t    Lepton_Pt;
   Float_t    Lepton_Eta;
   Float_t    Lepton_Phi;
   Float_t    Lepton_Energy;
   Float_t    Neutrino_Pt;
   Float_t    Neutrino_Eta;
   Float_t    Neutrino_Phi;
   Float_t    Neutrino_Energy;
   Float_t    Leptonic_W_Pt;
   Float_t    Leptonic_W_Eta;
   Float_t    Leptonic_W_Phi;
   Float_t    Leptonic_W_Energy;
   Float_t    Hadronic_W_Pt;
   Float_t    Hadronic_W_Eta;
   Float_t    Hadronic_W_Phi;
   Float_t    Hadronic_W_Energy;
   Float_t    Leptonic_Top_Pt;
   Float_t    Leptonic_Top_Eta;
   Float_t    Leptonic_Top_Phi;
   Float_t    Leptonic_Top_Energy;
   Float_t    Hadronic_Top_Pt;
   Float_t    Hadronic_Top_Eta;
   Float_t    Hadronic_Top_Phi;
   Float_t    Hadronic_Top_Energy;

};

#endif
