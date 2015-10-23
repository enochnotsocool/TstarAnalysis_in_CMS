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

   
   std::vector<float> _PtList;
   std::vector<float> _EtaList;
   std::vector<float> _PhiList;
   std::vector<float> _EnergyList;
   std::vector<float> _trackRelIsoList;
};

#endif 
