/*******************************************************************************
 *
 *  Filename    : NuisancePar.cc
 *  Description : Implementation for NuisancePar class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/NuisancePar.h"

NuisancePar::NuisancePar (const std::string& x , const std::string& y ):
      _name(x), _type(y){}
NuisancePar::~NuisancePar (){}

std::string NuisancePar::Name() const { return _name; }
std::string NuisancePar::Type() const { return _type; }
bool NuisancePar::operator==( const NuisancePar& x ) const { return _name==x._name; }
bool NuisancePar::operator<=( const NuisancePar& x ) const { return _name<=x._name;}
bool NuisancePar::operator>=( const NuisancePar& x ) const { return _name>=x._name;}
bool NuisancePar::operator<(  const NuisancePar& x ) const { return _name<x._name;}
bool NuisancePar::operator>(  const NuisancePar& x ) const { return _name>x._name;}

