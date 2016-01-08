/*******************************************************************************
 *
 *  Filename    : CombineMgr.h
 *  Description : Class for managing generation of HiggCombine requirement 
 *                for multiple channels
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef __COMBINEMGR_H__
#define __COMBINEMGR_H__

#include "TstarAnalysis/CombineAnalysis/interface/Enums.h"
#include "TstarAnalysis/CombineAnalysis/interface/HC_Process.h"
#include "TstarAnalysis/CombineAnalysis/interface/NuisancePar.h"
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include <map>

typedef std::pair<const ChannelName,ChannelMgr*> ChannelPair;
typedef std::map<const ChannelName,ChannelMgr*> ChannelMap;

class CombineMgr{
public:
   CombineMgr();
   virtual ~CombineMgr ();

   ChannelMgr* Channel( const ChannelName& ) ;

   void ParseCMDFile( const std::string& );
   void RunCombine( const ChannelName&, const SampleName&, const std::string& );
   void MakeLimitPlots();

private:
   ChannelMap   _channelList;

   void SetChannel( const std::string& , const std::string& );
   int  MassNumber( const SampleName& );
   std::string  MassNumberString( const SampleName& );
   std::string  LimitFile( const SampleName& , const std::string& );

};

#endif // __COMBINEMGR_H__
