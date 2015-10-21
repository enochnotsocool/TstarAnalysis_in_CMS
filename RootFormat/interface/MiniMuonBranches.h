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

   
   std::vector<TLorentzVector> _VecList;
   std::vector<float> _trackRelIsoList;
};

#endif 
