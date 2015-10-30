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
AnalysisMgr::AnalysisMgr( const std::string& tupledir ) :
   _tupleDir(tupledir)
{
   _outputFile = new TFile( "output.root" , "RECREATE" );
}

AnalysisMgr::~AnalysisMgr()
{
   for( auto sample : _sampleMap  ){ delete sample.second; }
   std::cout << "Closing_File" << std::endl;
   _outputFile->Close();
   std::cout << "Deleting pointer" << std::endl;
   delete _outputFile;
   std::cout << "Done" << std::endl;
}

//------------------------------------------------------------------------------ 
//   Public method implementation
//------------------------------------------------------------------------------
void AnalysisMgr::Print() const 
{
   std::cout << "*****************************************************" << std::endl;
   std::cout << "  Plot Manager" << std::endl;
   std::cout << "  Tuple Dir:  " << _tupleDir << std::endl;
   std::cout << "  Output   :  " << _outputFile << std::endl;
   std::cout << "  Luminocity: " << _totalLumi << std::endl;
   std::cout << "  Samples  :" << std::endl; 
   printAllSamples(); 
   std::cout << "*****************************************************" << std::endl;
}

void AnalysisMgr::printSample( const std::string& name ) 
{
   _sampleMap[name]->Print(_totalLumi);
}

void AnalysisMgr::printAllSamples() const 
{
   for( const auto& pair : _sampleMap ){
      pair.second->Print( _totalLumi ); }
}

void AnalysisMgr::addSample( const std::string& name ) 
{
   _sampleMap.insert( sampleKey( name , new SampleInfo(name,_tupleDir) ) ); 
}

SampleInfo* AnalysisMgr::sample( const std::string& name )
{
   SampleMap::iterator it = _sampleMap.find(name);
   if( it == _sampleMap.end() ) { return NULL; }
   else return it->second; 
}

void AnalysisMgr::makeBasicPlots()
{
   for( const auto& pair : _sampleMap ) {
      pair.second->makeBasicPlots(); }
}

void AnalysisMgr::setLumi( const float x ){ _totalLumi = x ; }
