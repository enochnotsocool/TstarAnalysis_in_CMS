#ifndef __MINIPARTICLE_H__
#define __MINIPARTICLE_H__

#include "TLorentzVector.h"

class MiniPARTICLE
{
public:
   MiniPARTICLE( size_t x ) { _index = x ; } 
   virtual ~MiniPARTICLE ();

   __ACCESS_FUNCTIONS__

private:
   size_t _index ;
};


#endif // __PARTICLE_H__
