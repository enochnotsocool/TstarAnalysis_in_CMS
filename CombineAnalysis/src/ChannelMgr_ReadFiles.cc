/*******************************************************************************
 *
 *  Filename    : ChannelMgr_ReadFiles.cc
 *  Description : Reading settings for combine analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include "CMSSW_Utils/Utils_Functions/interface/Utils.h"
#include "CMSSW_Utils/Utils_Types/interface/Parameter.h"

#include "TColor.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------ 
//   Helper functions
//------------------------------------------------------------------------------
bool ParseSampleLine( const string& , string&, Parameter& );

//------------------------------------------------------------------------------ 
//   ChannelMgr Public Members - Initializing by file
//------------------------------------------------------------------------------
void ChannelMgr::SetSampleWeight( const std::string& filename )
{
   ifstream input( filename );
   string line;
   string name;
   Parameter  para;
   while( getline(input,line) ){
      if( ParseSampleLine(line,name,para) && HasSample(name) ){
         Sample(name).SetSampleWeight(para);
      }
   }
}

void ChannelMgr::SetSelectionEfficiency( const std::string& filename )
{
   ifstream input( filename );
   string line;
   string name;
   Parameter  para;
   while( getline(input,line) ){
      if( ParseSampleLine(line,name,para) && HasSample(name) ){
         Sample(name).SetSelectionEff(para);
      }
   } 
}

void ChannelMgr::SetSampleInput( const std::string& filename )
{
   ifstream input( filename );
   vector<string> tokens;
   string line;
   string name;
   while( getline(input,line) ){
      if( !BreakLineToWords(line,tokens) ){ continue; }
      if( tokens.size() < 2 ) { continue; }
      name = tokens[0] ;
      if( HasSample(name) ){
         Sample(name).AddFile(tokens[1]);
      }
   }  
}

void ChannelMgr::SetSampleColor( const string& filename )
{
   ifstream input( filename );
   vector<string> tokens;
   string line;
   string name;
   string hex;
   while( getline(input,line) ){
      if( !BreakLineToWords(line,tokens) ){ continue; }
      if( tokens.size() < 2 ) { continue; }
      name = tokens[0] ;
      hex  = "#" + tokens[1];
      if( _MCSampleTable.HasList(name) && name != "Signal" ){
         cout << "Color" << TColor::GetColor(hex.c_str() ) << endl;
         _MCSampleTable[name].SetFillColor( (Color_t)TColor::GetColor(hex.c_str()) );
         _MCSampleTable[name].SetLineColor( (Color_t)TColor::GetColor(hex.c_str()) );
      }
   }
}


//------------------------------------------------------------------------------ 
//   Helper functions
//------------------------------------------------------------------------------
bool ParseSampleLine( const string& line, string& x , Parameter& y )
{
   vector<string> tokens; 
   float centralValue;
   float upperError;
   float lowerError;

   if(! BreakLineToWords( line, tokens )) { return false; }

   if( tokens.size() < 2 ) { return false; }
   x = tokens[0] ;
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

