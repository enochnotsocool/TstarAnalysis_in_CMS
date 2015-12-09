#ifndef __JetBRANCHES_H__
#define __JetBRANCHES_H__

#include "TTree.h"
#define MAX_OBJS 128

class JetBranches {
public:
   JetBranches() {}
   virtual ~JetBranches () {}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );

   UInt_t    Size;
   Float_t   Pt[MAX_OBJS];
   Float_t   Eta[MAX_OBJS];
   Float_t   Phi[MAX_OBJS];
   Float_t   Energy[MAX_OBJS];
   Float_t   BTag[MAX_OBJS];

};

#endif
