/*******************************************************************************
 *
 *  Filename    : HC_Process.h
 *  Description : Minimal information to pass to HiggsCombine Package
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __HC_PROCESS_H__
#define __HC_PROCESS_H__

#include "TstarAnalysis/CombineAnalysis/interface/NuisancePar.h"
#include "TH1F.h"
#include <string>
#include <map>

typedef std::map<const NuisancePar,float> NuisanceMap;

class HC_Process
{
public:
   HC_Process(const std::string&, const std::string& );
   virtual ~HC_Process ();
   
   const std::string& GetChannel() const { return _channelName; }
   const std::string& GetProcess() const { return _processName; }
   const std::string ObjName() const { return _channelName+"_"+_processName; }

   void   Noramlize();
   void   SetShape( TH1F* x ) { _shape_hist = x; }
   TH1F*  GetShape() const { return _shape_hist; }
   void   SetRate( double x ) { _rate = x ; }
   double GetRate() const { return _rate; }

private:
   const std::string&  _channelName;
   const std::string&  _processName;
   TH1F*   _shape_hist;
   // TH1F* _shape_systematics;
   double  _rate;
};

#endif // __HC_PROCESS_H__
