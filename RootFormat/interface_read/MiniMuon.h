#ifndef __MINIMuon_H__
#define __MINIMuon_H__

#include "TLorentzVector.h"

class MiniMuon
{
public:
   MiniMuon( size_t x ) { _index = x ; } 
   virtual ~MiniMuon ();

   
  const float& Pt();
  const float& Eta();
  const float& Phi();
  const float& Energy();
  const float& trackRelIso();

private:
   size_t _index ;
};


#endif // __Muon_H__
