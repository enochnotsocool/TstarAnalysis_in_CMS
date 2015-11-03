#ifndef __MINIMuonBRANCHES_H__
#define __MINIMuonBRANCHES_H__

#include "TTree.h"
#include "TLorentzVector.h"

class MiniMuonBranches{
public:
   MiniMuonBranches(){}
   virtual ~MiniMuonBranches (){}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );
   size_t size();
   void clear();

   
   std::vector<float> Pt;
   std::vector<float>* PtPtr;
   std::vector<float> Eta;
   std::vector<float>* EtaPtr;
   std::vector<float> Phi;
   std::vector<float>* PhiPtr;
   std::vector<float> Energy;
   std::vector<float>* EnergyPtr;
   std::vector<float> trackRelIso;
   std::vector<float>* trackRelIsoPtr;
};

#endif 
