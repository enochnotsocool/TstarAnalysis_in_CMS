/*******************************************************************************
 *
 *  Filename    : ChannelMgr.cc
 *  Description : Plot merging class implementation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"

#include "CMSSW_Utils/Utils_Functions/interface/Utils.h"
#include <iostream>

using namespace std;

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
float ChannelMgr::_totalLumi = 0.0;

ChannelMgr::ChannelMgr( const string& name, const string& latex ):
   _name(name), 
   _latex_name(latex),
   _dataSample("Data","Data"),
   _MCSampleTable(availableSamples)
{
}

ChannelMgr::~ChannelMgr()
{
}

//------------------------------------------------------------------------------ 
//   Private member functions - Access helpers
//------------------------------------------------------------------------------
const string ChannelMgr::MakeRootName() const 
{
   string ans = _latex_name;
   ConvertToRootFlavorLatex(ans);
   return ans;
}

const string ChannelMgr::MakeLatexName() const 
{
   string ans = _latex_name;
   ConvertToRegularLatex(ans);
   return ans;
}

SampleMgr& ChannelMgr::Sample( const string& input )
{
   if( input == "Data" ) return _dataSample;
   return _MCSampleTable.Sample(input);
}

const SampleMgr& ChannelMgr::Sample( const string& input ) const
{
   if( input == "Data" ) return _dataSample;
   return _MCSampleTable.Sample(input);
}

bool ChannelMgr::HasSample( const string& input ) const
{
   if( input == "Data" ) return true;
   return _MCSampleTable.HasSample(input);
}

bool ChannelMgr::HasSample( const string& listname, const string& samplename ) const
{
   for( const auto& list : _MCSampleTable ){
      if( list.Name() != listname ) { 
         continue; }
      for( const auto& sample : list ){
         if( sample.Name() == samplename ){
            return true; }
      }
   }
   return false;
}

void ChannelMgr::MakeBasicPlots()
{
   _dataSample.MakeBasicPlots();
   for( auto& list : _MCSampleTable ){
      for( auto& sample : list ){
         sample.MakeBasicPlots();
      }
   }
}
