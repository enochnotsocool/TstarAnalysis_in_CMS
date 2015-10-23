#ifndef __MINIElectron_H__
#define __MINIElectron_H__

#include "TLorentzVector.h"

class MiniElectron
{
public:
   MiniElectron( size_t x ) { _index = x ; } 
   virtual ~MiniElectron ();

   
  const float& Pt();
  const float& Eta();
  const float& Phi();
  const float& Energy();

private:
   size_t _index ;
};


#endif // __Electron_H__
