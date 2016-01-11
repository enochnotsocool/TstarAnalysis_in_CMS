/*******************************************************************************
 *
 *  Filename    : Utils.h
 *  Description : Utility functions 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __UTILS_H__
#define __UTILS_H__

#include "TH1F.h"
#include "TLorentzVector.h"
#include <iostream>

#include "DataFormats/Math/interface/LorentzVector.h"

extern void FillHistAtBin( TH1F* hist , int& counter );
extern std::ostream& operator<<( std::ostream&, const TLorentzVector& );
extern TLorentzVector ToRootFormat( const math::XYZTLorentzVector& );

#endif // __UTILS_H__
