/*******************************************************************************
 *
 *  Filename    : CombineMgr.cc
 *  Description : Implementation for CombineMgr class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TstarAnalysis/Utils/interface/Utils.h"
#include <fstream>

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
   for( auto& process : _processList ){
      delete process;
   }
   for( auto& channelpair : _channelList ){
      delete channelpair.second;
   }
}

//------------------------------------------------------------------------------ 
//   File Parser
//------------------------------------------------------------------------------
void CombineMgr::ParseCMDFile( const string& filename )
{
   ifstream input( filename );
   string cmd;
   string line;
   vector<string> tokens;

   while( getline( input, line ) ){
      if( !BreakLineToWords( line, tokens ) ) { continue; }
      
      cmd = tokens[0];
      if( cmd == "SetChannel" && tokens.size() == 3 ){
         SetChannel( tokens[1], tokens[2] ); 
      } else if( cmd == "MakeCombine" && tokens.size() == 1 ){
         MakeCombine();
      } 
      else {
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
   return _channelList[x];
} 


//------------------------------------------------------------------------------ 
//   Helper private functions
//------------------------------------------------------------------------------
void CombineMgr::SetChannel( const string& x , const string& filename )
{
   const ChannelName name = ChannelFromString( x );
   if( name == CHANNEL_END ) { 
      cerr << "Error! Unrecognized channel " << x << endl;
      return; 
   }
   _channelList[name]->ParseCMDFile( filename );
}

