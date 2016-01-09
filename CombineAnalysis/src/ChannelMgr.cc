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
#include <iostream>

using namespace std;

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
float ChannelMgr::_totalLumi = 0.0;

ChannelMgr::ChannelMgr( const ChannelName x )
{
   _name = x ;
   initSamples();
}

ChannelMgr::~ChannelMgr()
{
   for( auto pair : _MCsignalMap     ) { delete pair.second; }
   for( auto pair : _MCbackgroundMap ) { delete pair.second; }
   delete _dataSample;
}

//------------------------------------------------------------------------------ 
//   Public method implementation
//------------------------------------------------------------------------------
void ChannelMgr::Print() const 
{
   std::cout << "*****************************************************" << std::endl;
   std::cout << "Channel Manager" << std::endl;
   std::cout << "Luminocity : " << _totalLumi  << std::endl;
   printAllSamples(); 
   std::cout << "*****************************************************" << std::endl;
}

void ChannelMgr::printSample( const SampleName& name ) 
{
   sample( name )->Print(_totalLumi);
}

void ChannelMgr::printTable() const 
{
   _dataSample->Print( _totalLumi );
   printf( "Sample Name & Raw Events & XSection & Eff & Weight & Exp. Yeild \\\\\n" );
   for( const auto& pair: _MCbackgroundMap ){
      pair.second->PrintTable( _totalLumi ); 
   }
}


void ChannelMgr::printAllSamples() const 
{
   Parameter total_background(0.);
   std::cout << "\n*** Data Samples ************************************" << std::endl;
   _dataSample->Print( _totalLumi );
   std::cout << "\n*** MC Signals   ************************************" << std::endl;
   for( const auto& pair : _MCsignalMap ) {
      pair.second->Print( _totalLumi ); }
   std::cout << "\n*** MC Background ***********************************" << std::endl;
   for( const auto& pair : _MCbackgroundMap ){
      pair.second->Print( _totalLumi );
      total_background += pair.second->getExpectedYield( _totalLumi );
   }
   std::cout << "\n*** MC Background: " << total_background << "Events" << std::endl;
}

SampleMgr* ChannelMgr::sample( const SampleName& name )
{
   static SampleMap::iterator it;
   if( name == _dataSample->name() ) {return _dataSample;}
   it = _MCsignalMap.find(name);
   if( it != _MCsignalMap.end() ) { return it->second; }
   it = _MCbackgroundMap.find(name);
   if( it != _MCbackgroundMap.end() ) { return it->second; }
   return NULL;
}

const SampleMgr* ChannelMgr::sample( const SampleName& name ) const
{
   static SampleMap::const_iterator it;
   if( name == _dataSample->name() ) {return _dataSample;}
   it = _MCsignalMap.find(name);
   if( it != _MCsignalMap.end() ) { return it->second; }
   it = _MCbackgroundMap.find(name);
   if( it != _MCbackgroundMap.end() ) { return it->second; }
   return NULL;
}

void ChannelMgr::MakeBasicPlots()
{
   _dataSample->makeBasicPlots();
   for( const auto& pair : _MCsignalMap ) {
      pair.second->makeBasicPlots(); }
   for( const auto& pair : _MCbackgroundMap ){
      pair.second->makeBasicPlots(); }
}

void ChannelMgr::setLumi( const float x ){ _totalLumi = x ; }

bool ChannelMgr::setSignalMass( const SampleName& input )
{
   static SampleMap::iterator it;
   it = _MCsignalMap.find( input );
   if( it == _MCsignalMap.end() ) return false;
   _currentSignal = it->second ;
   return true;
}

const string ChannelMgr::plotfilepath( const string& name ) const
{
   return "./data/plots/" + Stringify(_name) + "/" + name + ".eps";
}


