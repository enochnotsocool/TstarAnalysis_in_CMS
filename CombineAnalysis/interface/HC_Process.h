/*******************************************************************************
 *
 *  Filename    : HC_Process.h
 *  Description : Minimal information to pass to HiggsCombine Package
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __HC_PROCESS_H__
#define __HC_PROCESS_H__

#include "TstarAnalysis/CombineAnalysis/interface/Enums.h"
#include "TstarAnalysis/CombineAnalysis/interface/NuisancePar.h"
#include "TH1F.h"
#include <string>
#include <map>

typedef std::map<const NuisancePar,float> NuisanceMap;

class HC_Process
{
public:
   HC_Process(const ChannelName, const SampleName);
   virtual ~HC_Process ();
   
   ChannelName GetChannel() const ;
   SampleName  GetProcess() const ;
   std::string ObjName() const;

   void   SetShape( TH1F* x );
   TH1F*  GetShape() const ;
   void   SetRate( double x );
   double GetRate() const ;
   void   AddNuisance( const NuisancePar& x , float y ); 
   NuisanceMap& GetNuisance() ;
   const NuisanceMap& GetNuisance() const;

   // Required for maps
   bool operator==( const HC_Process& ) const;
   bool operator<( const HC_Process& ) const;
   bool operator>( const HC_Process& ) const;
private:
   ChannelName  _channelName;
   SampleName   _processName;
   TH1F*   _shape_hist;
   // TH1F* _shape_systematics;
   double  _rate;
   NuisanceMap _nuisance;
};

#endif // __HC_PROCESS_H__
