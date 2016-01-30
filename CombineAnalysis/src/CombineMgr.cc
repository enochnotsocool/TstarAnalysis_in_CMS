/*******************************************************************************
 *
 *  Filename    : CombineMgr.cc
 *  Description : Implementation for CombineMgr class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "CMSSW_Utils/Utils_Functions/interface/Utils.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <memory>

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
   
   while( getline(file,line) ){
      if(!BreakLineToWords(line,tokens,"|")){ continue; }
      for( auto& token : tokens ){ StripTrailingSpace(token); }

      if( tokens.size() != 2 ){ continue; } 
      const string& name      = tokens[0];
      const string& latexname = tokens[1];
      if( HasChannel(name) ){
         cerr << "Warning! Skipping over duplicate channel (" << name 
              << ") at line (" << line_num << ") of file (" << filename << ")" << endl;
         continue;
      } else {
         cerr << "Making new channel (" << name << ")" << endl;
      }
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
   for( const auto& sampleList : availableSamples ){
      for( const auto& sample : sampleList ){
         ans.push_back( sample.Name() ); }
   }
   return ans;
}
vector<string> CombineMgr::AvailableChannels() const 
{
   vector<string> ans;
   for( const auto& channel : _channelList ){
      ans.push_back(channel->Name()); }
   return ans;
}

void CombineMgr::MakeBasicPlots()
{
   for( auto& channel : _channelList ) { channel->MakeBasicPlots(); }
}

void CombineMgr::MakeDataBGPlot( const string ch ,  const string pl )
{ 
   Channel(ch)->MakeDataBGPlot(pl); 
}

void CombineMgr::HC_MakeRequirements( const string ch )
{
   for( const auto& sample : availableSamples["Signal"] ){
      cerr << "Making requirements for sample (" << sample.Name() << ")" << endl;
      Channel(ch)->MakeLimitRequirement( sample.Name() );
   }
}

void CombineMgr::HC_RunCombine( const string ch, const string method )
{
   for( const auto& sample : availableSamples["Signal"] ){
      Channel(ch)->RunCombine( sample.Name() , method );
   }

   // Waiting for commands to finish!
   const string  user     = getenv( "USER" );
   const string& checkcmd = "combine";
   char runcmd[1024];
   bool wait = true;
   char buffer[128];
   string result = "";
   int  instance = 0 ;

   sprintf( runcmd , "ps -u %s | grep %s | wc -l" , user.c_str() , checkcmd.c_str() );
   while( wait ){
      std::shared_ptr<FILE> pipe(popen(runcmd, "r"), pclose);
      if (!pipe) { cerr << "Warning! Error during process checking" << endl;}

      fgets(buffer, 128, pipe.get()); // Getting first line of output to string
      result = buffer;
      instance = StrToInt( result );
      if( instance == 0 ){ wait = false;  break; }
      cout << "\rStill " << instance << " instances of " << checkcmd << "running! " << currentDateTime() << flush; 
      system("sleep 5");
   }
   cout << "\n All " << checkcmd << " finished at " << currentDateTime() << endl;
}

void CombineMgr::HC_PlotLimit( const string ch , const string method ) const
{
   Channel(ch)->MakeLimitPlot( method );
}

bool CombineMgr::HasChannel( const std::string& name ) const 
{
   for( const auto& channel : _channelList ){
      if( channel->Name() == name ){
         return true; }
   }
   return false;
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

