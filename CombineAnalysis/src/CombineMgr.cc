/*******************************************************************************
 *
 *  Filename    : CombineMgr.cc
 *  Description : Implementation for CombineMgr class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/CombineCommands.h"
#include "TstarAnalysis/Utils/interface/Utils.h"

#include <fstream>
#include <iostream>

using namespace std;

//------------------------------------------------------------------------------ 
//   Declaring Global variables
//------------------------------------------------------------------------------
CombineMgr*  cmbMgr = NULL;

//------------------------------------------------------------------------------ 
//   Constructor
//------------------------------------------------------------------------------
CombineMgr::CombineMgr()
{
   _channelList.insert( ChannelPair(ggMuon, new ChannelMgr(ggMuon)) );
}

CombineMgr::~CombineMgr()
{
   for( auto& channelpair : _channelList ){
      delete channelpair.second;
   }
   for( auto cmd : _cmdList ){
      delete cmd;
   }
}

bool CombineMgr::InitCommands()
{
   if( !addCommand( new SetCrossSection        ) ||
       !addCommand( new SetSelectionEfficiency ) ||
       !addCommand( new SetSampleWideWeight    ) ||
       !addCommand( new SetSampleInput         ) ||
       !addCommand( new MakeBasicPlots         ) ||
       !addCommand( new MakeDataBGPlot         ) ||
       !addCommand( new MakeSignalPlot         ) ||
       !addCommand( new MakeLimitRequirement   ) ||
       !addCommand( new RunCombine             ) ||
       !addCommand( new WaitCMD                ) ||
       !addCommand( new MakeLimitPlot          )    ) {
      cerr << "Error initializing command!" << endl;
      return false;
   }
   return true;
}


void CombineMgr::ParseCMDFile( const string& filename )
{
   ifstream input( filename );
   string cmd;
   string line;
   vector<string> tokens;

   while( getline( input, line ) ){
      if( !BreakLineToWords( line, tokens ) ) { continue; }
      
      cmd = tokens[0];
      tokens.erase( tokens.begin() );
      const CombineCMD* thiscmd = command( cmd );
      if( thiscmd != NULL ){
         thiscmd->execute( tokens );
      } else {
         cerr << "Error! Unrecognised command \"" << cmd << "\"" << endl;
         continue;
      }
   }
}


//------------------------------------------------------------------------------ 
//   Access Members
//------------------------------------------------------------------------------
ChannelMgr* CombineMgr::Channel( const ChannelName& x )
{
   if( _channelList.find(x) != _channelList.end() ){
      return _channelList.at(x);
   } else {
      return NULL;
   }
} 

const ChannelMgr* CombineMgr::Channel( const ChannelName& x ) const
{
   if( _channelList.find(x) != _channelList.end() ){
      return _channelList.at(x);
   } else {
      return NULL;
   }
}

ChannelMgr* CombineMgr::Channel( const string& x )
{
   return Channel( ChannelFromString(x) );
}

const ChannelMgr* CombineMgr::Channel( const string& x ) const 
{
   return Channel( ChannelFromString(x) );
}

const CombineCMD* CombineMgr::command( const string& x ) const
{
   for( const auto cmd : _cmdList ){
      if( cmd->cmd() == x ) { return cmd; }
   }
   return NULL;

}

bool CombineMgr::addCommand( const CombineCMD* x )
{
   for( const auto cmd : _cmdList ){
      if( x->cmd() == cmd->cmd() ) { return false; }
   } 
   _cmdList.push_back(x);
   return true;
}

