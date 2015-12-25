/*******************************************************************************
 *
 *  Filename    : CombineMgr_ReadFiles.cc
 *  Description : Reading settings for combine analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/Parameter.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

//------------------------------------------------------------------------------ 
//   Parsing CMD files
//------------------------------------------------------------------------------
void CombineMgr::ParseCMDFile( const string& filename ) 
{
   ifstream input( filename );
   string line;

   cout << "Begin File Reading!" << endl;
   while( getline(input,line) ){
      cout << "Raw input: " << line << endl;
      istringstream iss( line );
      vector<string> tokens{
         istream_iterator<string>{iss},
         istream_iterator<string>{}};
      if( tokens.empty() ){ continue; }

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
bool ParseSampleLine( const string& , SampleName&, Parameter& );

void CombineMgr::SetCrossSections( const std::string& filename )
{
   ifstream input( filename );
   string   line;
   vector<string> tokens;
   istringstream sstream;
   
   SampleName name;
   Parameter  para;
   
   //----- Getting Luminocity  ----------------------------------------------------
   getline( input , line );
   sstream.str( line );
   sstream >> _totalLumi ; 

   //----- Parsing Sample List   --------------------------------------------------
   while( getline(input, line ) ){
      if( ParseSampleLine(line,name,para) ){
         sample(name)->setCrossSection( para );
      }
   }
}

void CombineMgr::SetSampleWideWeights( const std::string& filename )
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

void CombineMgr::SetSelectionEfficiency( const std::string& filename )
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

void CombineMgr::SetSampleInputs( const std::string& filename )
{
   ifstream input( filename );
   string line;
   string namestring;
   string filestring;
   SampleName name;
   while( getline(input,line) ){
      istringstream iss(line);
      iss >> namestring >> filestring ;
      name = SampleFromString( namestring );
      sample(name)->addFile( filestring );
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

bool ParseSampleLine( const string& line, SampleName& x , Parameter& y )
{
   vector<string> tokens; 
   istringstream iss( line );
   float centralValue;
   float upperError;
   float lowerError; 

   copy( istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(tokens));

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

