/*******************************************************************************
 *
 *  Filename    : Parameter.cc
 *  Description : Parameters functions 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#include "TstarAnalysis/CombineAnalysis/interface/Parameter.h"
#include <math.h>

Parameter& Parameter::operator+=( const Parameter& x )
{
   _centralValue += x._centralValue;
   _upperError   += x._upperError;
   _lowerError   += x._lowerError;
   return *this;
}

Parameter Parameter::operator+( const Parameter& x ) const 
{
   Parameter ret = *this;
   ret += x;
   return ret;
}

Parameter Parameter::operator*( const float x ) const 
{
   return Parameter( _centralValue*x , _upperError*x , _lowerError*x);
}

Parameter operator*( const float x, const Parameter& p )
{
   return p*x;
}

Parameter Parameter::operator*( const Parameter& x ) const
{
   float newCentral = _centralValue * x._centralValue ;
   float au = RelativeUpperError();
   float bu = x.RelativeUpperError();
   float al = RelativeLowerError();
   float bl = x.RelativeLowerError();
   float newUpper   = newCentral * sqrt( au*au + bu*bu );
   float newLower   = newCentral * sqrt( al*al + bl*bl );
   return Parameter( newCentral, newUpper, newLower );
}

std::ostream& operator<<( std::ostream& s, const Parameter& x )
{
   s << x._centralValue << "(+" << x._upperError << "/-" << x._lowerError << ")";
   return s;
}


