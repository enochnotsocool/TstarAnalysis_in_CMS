/*******************************************************************************
 *
 *  Filename    : CombineMgr.cc
 *  Description : Implementation for CombineMgr class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/CombineCommands.h"
#include "CMSSW_Utils/Utils_Functions/interface/Utils.h"

#include <fstream>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

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
}

CombineMgr::~CombineMgr()
{
   for( auto& channel : _channelList ){
      delete channel;
   }
   for( auto cmd : _cmdList ){
      delete cmd;
   }
}

//------------------------------------------------------------------------------ 
//   Corresponding Commands, Error parsing handled by python code
//------------------------------------------------------------------------------
void CombineMgr::InitPlots( const string filename )
{
   availablePlots.InitFromFile( filename );
}
void CombineMgr::InitSamples( const string filename )
{
   availableSamples.InitFromFile( filename );
}

void CombineMgr::InitChannels( const string filename )
{
   unsigned line_num = 0;
   ifstream file( filename );
   string line;
   vector<string> tokens;
   
   cout << "Initializing plots from file (" << filename << ") ..." << endl; 
   while( getline(file,line) ){
      cout << "\rReading line " << ++line_num << flush;
      if(!BreakLineToWords(line,tokens,"|")){ continue; }
      for( auto& token : tokens ){ StripTrailingSpace(token); }

      if( tokens.size() != 2 ){ continue; } 
      const string& name      = tokens[0];
      const string& latexname = tokens[1];
      _channelList.push_back( new ChannelMgr(name,latexname) );
   }
}

void CombineMgr::SetChannelSelection( const string ch , const string file ){
   Channel(ch)->SetSelectionEfficiency(file); }
void CombineMgr::SetChannelFile( const string ch , const string file ){
   Channel(ch)->SetSampleInput(file); }
void CombineMgr::SetChannelWeights( const string ch , const string file ){
   Channel(ch)->SetSampleWeight(file); }
void CombineMgr::SetChannelColors( const string ch, const string file ){
   Channel(ch)->SetSampleColor(file); }


vector<string> CombineMgr::AvailablePlots() const
{
   vector<string> ans;
   for( const auto& plot : availablePlots ){
      ans.push_back( plot.Name() ) ;}
   return ans;
}
vector<string> CombineMgr::AvailableSamples() const 
{
   vector<string> ans;
   for( const auto& sample : availableSamples ){
      ans.push_back( sample.Name() ); }
   return ans;
}
vector<string> CombineMgr::AvailableChannels() const 
{
   vector<string> ans;
   for( const auto& channel : _channelList ){
      ans.push_back(channel->Name()); }
   return ans;
}


bool CombineMgr::InitCommands()
{
   if( 
       !addCommand( new SetSelectionEfficiency ) ||
       !addCommand( new SetSampleWideWeight    ) ||
       !addCommand( new SetSampleInput         ) ||
       !addCommand( new MakeBasicPlots         ) ||
       !addCommand( new MakeDataBGPlot         ) ||
       !addCommand( new MakeSignalPlot         ) ||
       !addCommand( new MakeLimitRequirement   ) ||
       !addCommand( new MakeLatexSummary       ) ||
       !addCommand( new RunCombine             ) ||
       !addCommand( new WaitCMD                ) ||
       !addCommand( new MakeLimitPlot          )    ) {
      cerr << "Error initializing command!" << endl;
      return false;
   }
   return true;
}

void CombineMgr::RunInterface()
{
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

ChannelMgr* CombineMgr::Channel( const string& x )
{
   for( auto& channel : _channelList ){
      if( channel->Name() == x ){
         return channel; }
   }
   return NULL;
}

const ChannelMgr* CombineMgr::Channel( const string& x ) const 
{
   for( const auto& channel : _channelList ){
      if( channel->Name() == x ){
         return channel; }
   }
   return NULL;
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

