#ifndef __OBJECTBRANCHES_H__
#define __OBJECTBRANCHES_H__

#include "TTree.h"
#define MAX_OBJS 128

class OBJECTBranches{
public:
   OBJECTBranches(){}
   virtual ~OBJECTBranches (){}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );

   __DATA_MEMBERS__
};

#endif 
