/*******************************************************************************
 *
 *  Filename    : ChannelMgr_ReadFiles.cc
 *  Description : Reading settings for combine analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/Parameter.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

//------------------------------------------------------------------------------ 
//   Helper functions
//------------------------------------------------------------------------------
bool BreakLineToWords( const string& , vector<string>& );
bool ParseSampleLine( const string& , SampleName&, Parameter& );

//------------------------------------------------------------------------------ 
//   Parsing CMD files
//------------------------------------------------------------------------------

void ChannelMgr::ParseCMDFile( const string& filename ) 
{
   ifstream input( filename );
   string line;
   vector<string> tokens;

   while( getline(input,line) ){
      if( !BreakLineToWords( line, tokens ) ) { continue; }
      
      string cmd = tokens[0];
      if( cmd == "SetCrossSections" && tokens.size() == 2 ){
         SetCrossSections( tokens[1] );
      } else if( cmd == "SetSampleInputs" && tokens.size() == 2 ){
         SetSampleInputs( tokens[1] );
      } else if( cmd == "SetSampleWideWeights" && tokens.size() == 2 ){
         SetSampleWideWeights( tokens[1] );
      } else if( cmd == "SetSelectionEfficiency" && tokens.size() == 2 ){
         SetSelectionEfficiency( tokens[1] );
      } else if( cmd == "ParseCMDFile" && tokens.size() == 2 ){
         ParseCMDFile( tokens[1] );
      } else if( cmd == "MakeBasicPlots" && tokens.size() == 1 ){
         MakeBasicPlots();
      } else if( cmd == "MakeDataToBGPlot" && tokens.size() == 2 ){
         MakeDataToBGPlot( PlotNameFromString( tokens[1] ) );
      } else if( cmd == "MakeSignalPlot" && tokens.size() == 2 ){
         MakeSignalPlot( PlotNameFromString( tokens[1] ) );
      } else if( cmd == "MakeInSampleComparison" && tokens.size() == 4 ){
         MakeInSampleComparison( SampleFromString( tokens[1] ),
               PlotNameFromString( tokens[2] ),
               PlotNameFromString( tokens[3] ) );
      }
      else {
         cerr << "Skipping unrecognised command/options " << endl;
         for( const string& x : tokens ){
            cerr << x << " " ;
         } cerr << endl;
      }
   }
}

//------------------------------------------------------------------------------ 
//   Configuration file Reading
//------------------------------------------------------------------------------

void ChannelMgr::SetCrossSections( const std::string& filename )
{
   ifstream input( filename );
   string   line;
   vector<string> tokens;
   
   SampleName name;
   Parameter  para;
   
   //----- Getting Luminocity  ----------------------------------------------------
   while( getline( input , line ) ){
      if( ParseSampleLine( line,name,para ) ){
         _totalLumi = para.CentralValue();
         break;
      }
   }

   //----- Parsing Sample List   --------------------------------------------------
   while( getline(input, line ) ){
      if( ParseSampleLine(line,name,para) ){
         sample(name)->setCrossSection( para );
      }
   }
}

void ChannelMgr::SetSampleWideWeights( const std::string& filename )
{
   ifstream input( filename );
   string line;
   SampleName name;
   Parameter  para;
   while( getline(input,line) ){
      if( ParseSampleLine(line,name,para) ){
         sample(name)->setSampleWeight(para.CentralValue());
      }
   }
}

void ChannelMgr::SetSelectionEfficiency( const std::string& filename )
{
   ifstream input( filename );
   string line;
   SampleName name;
   Parameter  para;
   while( getline(input,line) ){
      if( ParseSampleLine(line,name,para) ){
         sample(name)->setSelectionEff(para);
      }
   } 
}

void ChannelMgr::SetSampleInputs( const std::string& filename )
{
   ifstream input( filename );
   vector<string> tokens;
   string line;
   SampleName name;
   while( getline(input,line) ){
      if( !BreakLineToWords(line,tokens) ){ continue; }
      if( tokens.size() < 2 ) { continue; }
      name = SampleFromString( tokens[0] );
      if( name == DUMMY_END ){ continue; } 
      sample(name)->addFile( tokens[1] );
   }  
}

//------------------------------------------------------------------------------ 
//   Helper functions
//------------------------------------------------------------------------------
float StrToFloat( const string& x )
{
   float ans;
   istringstream iss( x );
   iss >> ans;
   return ans;
}

bool BreakLineToWords( const string& line, vector<string>& words )
{
   vector<string> temp;
   istringstream iss(line);
   copy( istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(temp));
   words = temp;
   // Comment handling
   if( words.empty() ) { return false; }
   if( words[0][0] == '#' ) { return false; }
   return true;
}

bool ParseSampleLine( const string& line, SampleName& x , Parameter& y )
{
   vector<string> tokens; 
   float centralValue;
   float upperError;
   float lowerError;

   if(! BreakLineToWords( line, tokens )) { return false; }

   if( tokens.size() < 2 ) { return false; }
   x = SampleFromString( tokens[0] );
   centralValue = StrToFloat( tokens[1] );
   if( tokens.size() == 3 ){
      upperError = lowerError = StrToFloat( tokens[2] );
   } else if( tokens.size() == 4 ) {
      upperError = StrToFloat( tokens[2] );
      lowerError = StrToFloat( tokens[3] );
   } else {
      upperError = lowerError = 0.;
   }

   y.SetCentralValue( centralValue );
   y.SetUpperError( upperError );
   y.SetLowerError( lowerError );
   return true;
}

