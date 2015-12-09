#ifndef __EventBRANCHES_H__
#define __EventBRANCHES_H__

#include "TTree.h"
#define MAX_OBJS 128

class EventBranches {
public:
   EventBranches() {}
   virtual ~EventBranches () {}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );

   UInt_t      RunNumber;
   ULong64_t   LumiNumber;
   UInt_t      EventNumber;
   UInt_t      BunchCrossingNumber;
   UInt_t      pileUp;
   Float_t     MET;
   Float_t     METPhi;
   Float_t     eventWeight;
   Float_t     chiSqMass;

};

#endif
