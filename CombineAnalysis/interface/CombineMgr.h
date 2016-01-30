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

#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include <vector>

//------------------------------------------------------------------------------ 
//   Forwards declaration for classes (and typedefs)
//------------------------------------------------------------------------------

class CombineMgr;
class CombineCMD;

//------------------------------------------------------------------------------ 
//   Combine command interface manager (boost python: don't use reference)
//------------------------------------------------------------------------------
class CombineMgr{
public:
   CombineMgr();
   virtual ~CombineMgr ();

   bool InitCommands();
   ChannelMgr* Channel( const std::string& );
   const ChannelMgr* Channel( const std::string& ) const;

   void InitPlots( const std::string );
   void InitSamples( const std::string );
   void InitChannels( const std::string );

   void SetChannelSelection( const std::string , const std::string );
   void SetChannelFile( const std::string , const std::string );
   void SetChannelWeights( const std::string, const std::string );
   void SetChannelColors( const std::string, const std::string );

   std::vector<std::string> AvailablePlots() const ;
   std::vector<std::string> AvailableSamples() const ;
   std::vector<std::string> AvailableChannels() const ;

   void RunInterface();
   void ParseCMDFile( const std::string& );

private:
   std::vector<ChannelMgr*> _channelList;
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
