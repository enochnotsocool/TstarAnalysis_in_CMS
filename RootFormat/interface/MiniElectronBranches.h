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

   
   std::vector<float> _PtList;
   std::vector<float> _EtaList;
   std::vector<float> _PhiList;
   std::vector<float> _EnergyList;
};

#endif 
