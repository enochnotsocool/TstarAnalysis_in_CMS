/*******************************************************************************
 *
 *  Filename    : EnumClassification.cc
 *  Description : Classifying various Enums
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/Enums.h"

bool SignalSample( const SampleName x )
{
   if( x > Tstar_M0700 ) { return false; }
   if( x < Tstar_M1600 ) { return false; }
   return true;
}
