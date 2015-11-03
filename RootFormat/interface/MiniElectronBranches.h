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

   
   std::vector<float> Pt;
   std::vector<float>* PtPtr;
   std::vector<float> Eta;
   std::vector<float>* EtaPtr;
   std::vector<float> Phi;
   std::vector<float>* PhiPtr;
   std::vector<float> Energy;
   std::vector<float>* EnergyPtr;
};

#endif 
