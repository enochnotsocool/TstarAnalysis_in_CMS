/*******************************************************************************
 *
 *  Filename    : CombineCommands.cc
 *  Description : Implementation of all command define in CombineCommands.h
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineCommands.h"
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TstarAnalysis/Utils/interface/Utils.h"
#include <iostream>
#include <stdlib.h>
#include <memory>

extern CombineMgr* cmbMgr;

using namespace std;

//------------------------------------------------------------------------------ 
//   Helper functions
//------------------------------------------------------------------------------
bool HasExactOptionCount( const vector<string>&, const unsigned );
bool ChannelNotFound( const string& );
bool SignalNotFound( const string& );
bool PlotNotFound( const string& );

//------------------------------------------------------------------------------ 
//   Defining command execution
//------------------------------------------------------------------------------
bool SetCrossSection::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 2 ) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound( options[0] ); }

   channel->SetCrossSection( options[1] );
   return true;
}

bool SetSelectionEfficiency::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 2 ) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound( options[0] );}

   channel->SetSelectionEfficiency( options[1] );
   return true;
}

bool SetSampleWideWeight::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 2 ) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound( options[0] ); }
   channel->SetSampleWideWeight( options[1] );
   return true;
}

bool SetSampleInput::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 2 ) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound(options[0]); }
   channel->SetSampleInput( options[1] );
   return true;
}

bool MakeBasicPlots::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 1 ) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound( options[0] ); }
   channel->MakeBasicPlots();
   return true;
}

bool MakeDataBGPlot::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 2 ) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound(options[0]); }
   const PlotName x = PlotNameFromString( options[1] );
   if( x == PLOTNAME_END ) { return PlotNotFound(options[1]); } 
   channel->MakeDataToBGPlot( x );
   return true;
}

bool MakeSignalPlot::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 2 ) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound(options[0]); }
   const PlotName x = PlotNameFromString( options[1] );
   if( x == PLOTNAME_END ) { return PlotNotFound(options[1]); } 
   channel->MakeSignalPlot( x );
   return true;
}

bool MakeLimitRequirement::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 2 ) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound(options[0]); }
   const SampleName x = SampleFromString( options[1] );
   if( !SignalSample(x) ) { return PlotNotFound(options[1]); } 
   channel->MakeLimitRequirement( x );
   return true;
}

bool RunCombine::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 3 ) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound(options[0]); }
   const SampleName x = SampleFromString( options[1] );
   if( !SignalSample(x) ) { return PlotNotFound(options[1]); } 
   channel->RunCombine( x , options[2] );
   return true; 
}



bool MakeLimitPlot::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 1) ) { return false; }
   ChannelMgr* channel = cmbMgr->Channel( options[0] );
   if( channel == NULL ){ return ChannelNotFound(options[0]); }
   channel->MakeLimitPlot();
   return true; 
}

bool WaitCMD::execute( const vector<string>& options ) const
{
   if( !HasExactOptionCount( options, 1 ) ) { return false; }
   const string  user     = getenv( "USER" );
   const string& checkcmd = options[0];
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
      if( instance == 0 ){ wait = false;  continue; }
      cout << "\rStill " << instance << " instances of " << checkcmd << "running! " << currentDateTime() << flush; 
      system("sleep 5");
   }
   cout << "\n All " << checkcmd << " finished at " << currentDateTime() << endl;
   return true;
}


//------------------------------------------------------------------------------ 
//   Helper function implementation
//------------------------------------------------------------------------------
bool HasExactOptionCount( const vector<string>& options, const unsigned n)
{
   if( options.size() > n ) { 
      cerr << "Error! Extra input (" << options[n] << ")!" << endl;
      return false;
   } else if( options.size() < n ){
      cerr << "Error! Missing input after (" << options.back() << ")!" << endl;
      return false;
   } else {
      return true;
   }
}

bool ChannelNotFound( const string& input )
{
   cerr << "Error! Input channel (" << input << ") not found!" << endl;
   return false;
}

bool PlotNotFound( const string& input )
{
   cerr << "Error! Input plot (" << input << ") not found!" << endl;
   return false;
}

bool SignalNotFound( const string& input )
{
   cerr << "Error! Input signal sample (" << input << ") not found!" << endl;
   return false;
}

