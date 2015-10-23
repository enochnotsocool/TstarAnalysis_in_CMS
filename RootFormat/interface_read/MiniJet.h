#ifndef __MINIJet_H__
#define __MINIJet_H__

#include "TLorentzVector.h"

class MiniJet
{
public:
   MiniJet( size_t x ) { _index = x ; } 
   virtual ~MiniJet ();

   
  const float& Pt();
  const float& Eta();
  const float& Phi();
  const float& Energy();

private:
   size_t _index ;
};


#endif // __Jet_H__
