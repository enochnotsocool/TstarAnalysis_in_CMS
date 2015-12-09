#ifndef __ElectronBRANCHES_H__
#define __ElectronBRANCHES_H__

#include "TTree.h"
#define MAX_OBJS 128

class ElectronBranches {
public:
   ElectronBranches() {}
   virtual ~ElectronBranches () {}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );

   UInt_t    Size;
   Float_t   Pt[MAX_OBJS];
   Float_t   Eta[MAX_OBJS];
   Float_t   Phi[MAX_OBJS];
   Float_t   Energy[MAX_OBJS];

};

#endif
