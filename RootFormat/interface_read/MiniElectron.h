#ifndef __MINIElectron_H__
#define __MINIElectron_H__

#include "TLorentzVector.h"

class MiniElectron
{
public:
   MiniElectron( size_t x ) { _index = x ; } 
   virtual ~MiniElectron ();

   
  const TLorentzVector& Vec();

private:
   size_t _index ;
};


#endif // __Electron_H__
