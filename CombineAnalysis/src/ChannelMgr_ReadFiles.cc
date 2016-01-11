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
#include "TstarAnalysis/Utils/interface/Utils.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------ 
//   Helper functions
//------------------------------------------------------------------------------
bool ParseSampleLine( const string& , SampleName&, Parameter& );

//------------------------------------------------------------------------------ 
//   Configuration file Reading
//------------------------------------------------------------------------------
void ChannelMgr::SetCrossSection( const std::string& filename )
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

void ChannelMgr::SetSampleWideWeight( const std::string& filename )
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

void ChannelMgr::SetSampleInput( const std::string& filename )
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

