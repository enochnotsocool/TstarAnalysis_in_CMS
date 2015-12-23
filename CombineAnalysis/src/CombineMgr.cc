/*******************************************************************************
 *
 *  Filename    : CombineMgr.cc
 *  Description : Plot merging class implementation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include <iostream>
//------------------------------------------------------------------------------ 
//   Declaring global 
//------------------------------------------------------------------------------
CombineMgr* cmbMgr = NULL;

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
CombineMgr::CombineMgr( const std::string& filename )
{
   _outputFile = new TFile( filename.c_str() , "RECREATE" );
   initSamples();
}

CombineMgr::~CombineMgr()
{
   for( auto pair : _MCsignalMap     ) { delete pair.second; }
   for( auto pair : _MCbackgroundMap ) { delete pair.second; }
   delete _dataSample;
   
   _outputFile->Close();
   delete _outputFile;

   delete _signalLegend;
}

//------------------------------------------------------------------------------ 
//   Public method implementation
//------------------------------------------------------------------------------
void CombineMgr::Print() const 
{
   std::cout << "*****************************************************" << std::endl;
   std::cout << "Plot Manager" << std::endl;
   std::cout << "Output     : " << _outputFile << std::endl;
   std::cout << "Luminocity : " << _totalLumi  << std::endl;
   printAllSamples(); 
   std::cout << "*****************************************************" << std::endl;
}

void CombineMgr::printSample( const SampleName& name ) 
{
   sample( name )->Print(_totalLumi);
}

void CombineMgr::printTable() const 
{
   _dataSample->Print( _totalLumi );
   printf( "Sample Name & Raw Events & XSection & Eff & Weight & Exp. Yeild \\\\\n" );
   for( const auto& pair: _MCbackgroundMap ){
      pair.second->PrintTable( _totalLumi ); 
   }
}


void CombineMgr::printAllSamples() const 
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

SampleMgr* CombineMgr::sample( const SampleName& name )
{
   static SampleMap::iterator it;
   if( name == _dataSample->name() ) {return _dataSample;}
   it = _MCsignalMap.find(name);
   if( it != _MCsignalMap.end() ) { return it->second; }
   it = _MCbackgroundMap.find(name);
   if( it != _MCbackgroundMap.end() ) { return it->second; }
   return NULL;
}

void CombineMgr::makeBasicPlots()
{
   _dataSample->makeBasicPlots();
   for( const auto& pair : _MCsignalMap ) {
      pair.second->makeBasicPlots(); }
   for( const auto& pair : _MCbackgroundMap ){
      pair.second->makeBasicPlots(); }
}

void CombineMgr::setLumi( const float x ){ _totalLumi = x ; }

bool CombineMgr::setSignalMass( const SampleName& input )
{
   static SampleMap::iterator it;
   it = _MCsignalMap.find( input );
   if( it == _MCsignalMap.end() ) return false;
   _currentSignal = it->second ;
   return true;
}
