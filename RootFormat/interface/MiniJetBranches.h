#ifndef __MINIJetBRANCHES_H__
#define __MINIJetBRANCHES_H__

#include "TTree.h"
#include "TLorentzVector.h"

class MiniJetBranches{
public:
   MiniJetBranches(){}
   virtual ~MiniJetBranches (){}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );
   size_t size();
   void clear();

   
   std::vector<TLorentzVector> _VecList;
   std::vector<float> _tempList;
};

#endif 
