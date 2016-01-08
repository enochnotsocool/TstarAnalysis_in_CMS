/*******************************************************************************
 *
 *  Filename    : CombineMgr_ReadCMD.cc
 *  Description : Commands for command processing 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TstarAnalysis/Utils/interface/Utils.h"
#include <fstream>

using namespace std;

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
      if( cmd == "SetCrossSection" && tokens.size() == 3 ){
         ChannelMgr* channel = _channelList.at( ChannelFromString(tokens[1]));
         if( channel != NULL ){
            channel->SetCrossSections( tokens[2] );
         }
      } else if( cmd == "SetSelectionEfficiency" && tokens.size() == 3 ){
         ChannelMgr* channel = _channelList.at( ChannelFromString(tokens[1]));
         if( channel != NULL ){
            channel->SetSelectionEfficiency( tokens[2] );
         }
      } else if( cmd == "SetSampleWideWeights" && tokens.size() == 3 ){
         ChannelMgr* channel = _channelList.at( ChannelFromString(tokens[1]));
         if( channel != NULL ){
            channel->SetSampleWideWeights( tokens[2] );
         }
      } else if( cmd == "SetSampleInputs" && tokens.size() == 3 ){
         ChannelMgr* channel = _channelList.at( ChannelFromString(tokens[1]));
         if( channel != NULL ){
            channel->SetSampleInputs( tokens[2] );
         }
      } else if( cmd == "MakeBasicPlots" && tokens.size() == 1 ){
         for( auto& pair : _channelList ){
            pair.second->MakeBasicPlots();
         }
      } else if( cmd == "RunCombine" && tokens.size() == 4 ){
         ChannelName ch = ChannelFromString(tokens[1]);
         SampleName  mp = SampleFromString(tokens[2]);
         RunCombine(ch,mp,tokens[3]);
      } else if( cmd == "MakeLimitPlots" && tokens.size() == 1 ){
         MakeLimitPlots();
      }
      else if( cmd == "MakeLimitRequirements" && tokens.size() == 3 ){
         ChannelMgr* channel   = _channelList.at( ChannelFromString(tokens[1]));
         SampleName  massPoint = SampleFromString(tokens[2]);
         channel->MakeLimitRequirements( massPoint );
      } 
      else {
         cerr << "Error! Unrecognised command \"" << cmd << "\"" << endl;
         continue;
      }
   }
}

