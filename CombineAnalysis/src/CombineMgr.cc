/*******************************************************************************
 *
 *  Filename    : CombineMgr.cc
 *  Description : Implementation for CombineMgr class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
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
   for( auto& channelpair : _channelList ){
      delete channelpair.second;
   }
}

//------------------------------------------------------------------------------ 
//   Access Members
//------------------------------------------------------------------------------
ChannelMgr* CombineMgr::Channel( const ChannelName& x )
{
   return _channelList.at(x);
} 


