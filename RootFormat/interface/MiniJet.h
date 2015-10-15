/*******************************************************************************
 *
 *  Filename    : MiniJet.h
 *  Description : Stripped down version of MiniAOD Jet 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : In this class we are storing only the variables we need from 
 *  a particle for the cross channel analysis.
 *
*******************************************************************************/
#ifndef __MINIJET_H__
#define __MINIJET_H__

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TLorentzVector.h"
#include <vector>
using namespace std;

class MiniJet{
public:
   MiniJet();
   virtual ~MiniJet ();


private:
   TLorentzVector _vec;
   float   _CSV_v2Btag;
};
#endif // __MINIJET_H__
