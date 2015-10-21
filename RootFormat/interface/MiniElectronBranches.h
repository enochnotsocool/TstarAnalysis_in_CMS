#ifndef __MINIElectronBRANCHES_H__
#define __MINIElectronBRANCHES_H__

#include "TTree.h"
#include "TLorentzVector.h"

class MiniElectronBranches{
public:
   MiniElectronBranches(){}
   virtual ~MiniElectronBranches (){}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );
   size_t size();
   void clear();

   
   std::vector<TLorentzVector> _VecList;
};

#endif 
