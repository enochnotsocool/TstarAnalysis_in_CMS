/*******************************************************************************
 *
 *  Filename    : MiniParticle.h
 *  Description : Common variable class for a particle
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Details: 
 *       Using Plain ROOT classes for storage rather than the CMSSW 
 *       counterparts, such as using TLorentzVector rather than
 *       math::XYZTLorentzVector.
 *
 *       Class is designed to be read only, all public members are constant 
 *       member.
 *  
*******************************************************************************/
#ifndef __MINIPARTICLE_H__
#define __MINIPARTICLE_H__

#include "TLorentzVector.h"

class MiniParticle
{
public:
   MiniParticle();
   virtual ~MiniParticle ();

   const TLorentzVector& p4() const;
   double pt()     const; 
   double eta()    const; 
   double phi()    const; 
   double energy() const; 
   double px()     const; 
   double py()     const; 
   double pz()     const; 
   double mass()   const; 

protected:
   TLorentzVector   _p4 ;
};

#endif // __MINIPARTICLE_H__
