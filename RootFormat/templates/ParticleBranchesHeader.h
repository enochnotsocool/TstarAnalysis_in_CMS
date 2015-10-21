#ifndef __MINIPARTICLEBRANCHES_H__
#define __MINIPARTICLEBRANCHES_H__

#include "TTree.h"
#include "TLorentzVector.h"

class MiniPARTICLEBranches{
public:
   MiniPARTICLEBranches(){}
   virtual ~MiniPARTICLEBranches (){}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );
   size_t size();
   void clear();

   __DATA_MEMBERS__
};

#endif 
