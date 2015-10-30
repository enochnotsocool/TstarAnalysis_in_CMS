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

   
   std::vector<float> _PtList;
   std::vector<float> _EtaList;
   std::vector<float> _PhiList;
   std::vector<float> _EnergyList;
   std::vector<float> _btagList;
};

#endif 
