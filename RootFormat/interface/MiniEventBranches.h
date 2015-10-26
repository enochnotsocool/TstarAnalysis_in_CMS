#ifndef __MINIEventBRANCHES_H__
#define __MINIEventBRANCHES_H__

#include "TTree.h"
#include "TLorentzVector.h"

class MiniEventBranches{
public:
   MiniEventBranches(){}
   virtual ~MiniEventBranches (){}
   void registerVariables( TTree* );
   void retrieveVariables( TTree* );
   size_t size();
   void clear();

   
   UInt_t _RunNumber;
   ULong64_t _LumiNumber;
   UInt_t _EventNumber;
   UInt_t _BunchCrossingNumber;
   UInt_t _pileUp;
   UInt_t _MuonCount;
   UInt_t _ElectronCount;
   UInt_t _JetCount;
   UInt_t _VertexCount;
   float _MET;
   float _METPhi;
};

#endif 
