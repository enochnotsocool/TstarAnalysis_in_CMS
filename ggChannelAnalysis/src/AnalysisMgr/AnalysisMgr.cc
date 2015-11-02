/*******************************************************************************
 *
 *  Filename    : AnalysisMgr.cc
 *  Description : Plot merging class implementation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#include "AnalysisMgr.h"
#include <iostream>
//------------------------------------------------------------------------------ 
//   Declaring global 
//------------------------------------------------------------------------------
AnalysisMgr* pltMgr = NULL;


//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
AnalysisMgr::AnalysisMgr( const std::string& filename )
{
   _outputFile = new TFile( filename.c_str() , "RECREATE" );
   initSamples();
}

AnalysisMgr::~AnalysisMgr()
{
   for( auto pair : _MCsignalMap     ) { delete pair.second; }
   for( auto pair : _MCbackgroundMap ) { delete pair.second; }
   delete _dataSample;
   
   _outputFile->Close();
   delete _outputFile;

   delete _combineLegend;
}

//------------------------------------------------------------------------------ 
//   Public method implementation
//------------------------------------------------------------------------------
void AnalysisMgr::Print() const 
{
   std::cout << "*****************************************************" << std::endl;
   std::cout << "Plot Manager" << std::endl;
   std::cout << "Output     : " << _outputFile << std::endl;
   std::cout << "Luminocity : " << _totalLumi  << std::endl;
   printAllSamples(); 
   std::cout << "*****************************************************" << std::endl;
}

void AnalysisMgr::printSample( const std::string& name ) 
{
   sample( name )->Print(_totalLumi);
}

void AnalysisMgr::printAllSamples() const 
{
   float total_background = 0;
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

SampleMgr* AnalysisMgr::sample( const std::string& name )
{
   static SampleMap::iterator it;
   if( name == _dataSample->name() ) {return _dataSample;}
   it = _MCsignalMap.find(name);
   if( it != _MCsignalMap.end() ) { return it->second; }
   it = _MCbackgroundMap.find(name);
   if( it != _MCbackgroundMap.end() ) { return it->second; }
   return NULL;
}

void AnalysisMgr::makeBasicPlots()
{
   _dataSample->makeBasicPlots();
   for( const auto& pair : _MCsignalMap ) {
      pair.second->makeBasicPlots(); }
   for( const auto& pair : _MCbackgroundMap ){
      pair.second->makeBasicPlots(); }
}

void AnalysisMgr::setLumi( const float x ){ _totalLumi = x ; }

bool AnalysisMgr::setSignalMass( const std::string& input )
{
   static SampleMap::iterator it;
   it = _MCsignalMap.find( input );
   if( it == _MCsignalMap.end() ) return false;
   _currentSignal = it->second ;
   return true;
}
