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
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include <vector>
#include <map>

//------------------------------------------------------------------------------ 
//   Forwards declaration for classes (and typedefs)
//------------------------------------------------------------------------------
typedef std::pair<const ChannelName,ChannelMgr*> ChannelPair;
typedef std::map<const ChannelName,ChannelMgr*> ChannelMap;

class CombineMgr;
class CombineCMD;

//------------------------------------------------------------------------------ 
//   Combine command interface manager
//------------------------------------------------------------------------------
class CombineMgr{
public:
   CombineMgr();
   virtual ~CombineMgr ();

   bool InitCommands();
   ChannelMgr* Channel( const ChannelName& ) ;
   const ChannelMgr* Channel( const ChannelName& ) const;
   ChannelMgr* Channel( const std::string& );
   const ChannelMgr* Channel( const std::string& ) const;

   void ParseCMDFile( const std::string& );

private:
   ChannelMap  _channelList;
   std::vector<const CombineCMD*>   _cmdList;

   bool  addCommand( const CombineCMD* );
   const CombineCMD* command( const std::string& ) const; 
};

//------------------------------------------------------------------------------ 
//   Base class for commands
//------------------------------------------------------------------------------
class CombineCMD
{
public:
   CombineCMD(){}
   virtual ~CombineCMD(){}
   virtual const std::string cmd() const = 0;
   virtual bool execute( const std::vector<std::string>& ) const = 0;
};

//------------------------------------------------------------------------------ 
//   Macros short hand for declaring new command
//------------------------------------------------------------------------------
#define DEFINE_CMD( COMMAND )                                        \
   class COMMAND : public CombineCMD {                               \
   public:                                                           \
      COMMAND(){}                                                    \
      virtual ~COMMAND(){}                                           \
      virtual const std::string cmd() const { return #COMMAND ; }    \
      virtual bool execute( const std::vector<std::string>& ) const; \
   };



#endif // __COMBINEMGR_H__