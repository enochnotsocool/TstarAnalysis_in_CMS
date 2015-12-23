/*******************************************************************************
 *
 *  Filename    : Parameter.h
 *  Description : Parameter with error bar for simple handling
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <iostream>

class Parameter
{
public:
   Parameter(){}
   Parameter(const float c,const float u=0.0,const float l=0.0):
      _centralValue(c), _upperError(u), _lowerError(l){}
   virtual ~Parameter(){}

   //----- Basic Access functions  ------------------------------------------------
   inline float CentralValue() const {return _centralValue;}
   inline float AbsoluteUpperError() const { return _upperError; }
   inline float AbsoluteLowerError() const { return _lowerError; }
   inline float RelativeUpperError() const { return _upperError/_centralValue; }
   inline float RelativeLowerError() const { return _lowerError/_centralValue; }

   void SetCentralValue( const float x ){ _centralValue = x; } 
   void SetUpperError( const float x ) { _upperError = x ; }
   void SetLowerError( const float x ) { _lowerError = x ; }

   //----- Functions defined in Parameter.cc  -------------------------------------
   Parameter& operator+=( const Parameter& ) ;
   Parameter operator+ ( const Parameter& ) const ;
   Parameter operator*( const Parameter& ) const;
   Parameter operator*( const float ) const;
   friend Parameter operator*( const float, const Parameter& );
   friend std::ostream& operator<< ( std::ostream& , const Parameter& );

private:
   float  _centralValue;
   float  _upperError;
   float  _lowerError;
};

#endif // __PARAMETER_H__

