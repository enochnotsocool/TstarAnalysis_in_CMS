/*******************************************************************************
 *
 *  Filename    : JetPermutator.h
 *  Description : Helper class for permutating Jets 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Note that the class is not generalized, but specializes for a two bjet 
 *  output with at least one bjet and at most 2 bjets, with a total of 
 *  6 outputs
 *
*******************************************************************************/
#ifndef __JETPERMUTATOR_H__
#define __JETPERMUTATOR_H__

#include "TLorentzVector.h"
#include <vector>
#include "DataFormats/PatCandidates/interface/Jet.h"

typedef std::vector<const pat::Jet*> JetList;

class JetPermutator {
public:
   JetPermutator(const JetList& , const JetList& );
   virtual ~JetPermutator ();

   //----- Access operators  ------------------------------------------------------
   TLorentzVector& operator[](const size_t i){ return _returnVector[i]; }
   const TLorentzVector& operator[](const size_t i)const{ return _returnVector[i];}

   //----- The class is analysis specific  ----------------------------------------
   const TLorentzVector& t_h_bjet()    const { return _returnVector[0]; }
   const TLorentzVector& t_l_bjet()    const { return _returnVector[1]; }
   const TLorentzVector& w_h_jet1()    const { return _returnVector[2]; }
   const TLorentzVector& w_h_jet2()    const { return _returnVector[3]; }
   const TLorentzVector& tstar_h_jet() const { return _returnVector[4]; }
   const TLorentzVector& tstar_l_jet() const { return _returnVector[5]; }

   bool permutate();
private:
   std::vector<TLorentzVector>  _returnVector;
   std::vector<const pat::Jet*> _rawbjetList;
   std::vector<const pat::Jet*> _rawljetList;

   void makeVectorList();
};

#endif // __JETPERMUTATOR_H__

