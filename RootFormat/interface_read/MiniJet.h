#ifndef __MINIJet_H__
#define __MINIJet_H__

#include "Global.h"

class MiniJet
{
public:
   MiniJet( size_t x ) { _index = x ; } 
   virtual ~MiniJet ();

   
  const TLorentzVector& Vec();
  const float& temp();

private:
   size_t _index ;
};


#endif // __Jet_H__
