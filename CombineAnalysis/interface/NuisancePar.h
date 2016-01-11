/*******************************************************************************
 *
 *  Filename    : NuisancePar.h
 *  Description : Nuisance Parameter class, only keeps track of name
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __NUISANCEPAR_H__
#define __NUISANCEPAR_H__

#include <string>

class NuisancePar
{
public:
   NuisancePar (const std::string& x , const std::string& y );
   virtual ~NuisancePar ();

   std::string Name() const;
   std::string Type() const;
   bool operator==( const NuisancePar& x )const;
   bool operator<=( const NuisancePar& x )const;
   bool operator>=( const NuisancePar& x )const;
   bool operator<(  const NuisancePar& x )const;
   bool operator>(  const NuisancePar& x )const;

private:
   std::string _name;
   std::string _type;
};

#endif // __NUISANCEPAR_H__
