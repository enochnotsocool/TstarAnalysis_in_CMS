/*******************************************************************************
 *
 *  Filename    : PlotMerging.cc
 *  Description : Plot merging class implementation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#include "PlotMerging.h"
#include <iostream>
//------------------------------------------------------------------------------ 
//   Declaring global 
//------------------------------------------------------------------------------
PlotMerging* pltMgr = NULL;


//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
PlotMerging::PlotMerging( const std::string& tupledir ) :
   _tupleDir(tupledir)
{
   _outputFile = new TFile( "output.root" , "RECREATE" );
   _stackHist  = NULL;
   _canvas     = NULL;
}

PlotMerging::~PlotMerging()
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
void PlotMerging::Print() const 
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

void PlotMerging::printSample( const std::string& name ) 
{
   _sampleMap[name]->Print();
}

void PlotMerging::printAllSamples() const 
{
   for( const auto& pair : _sampleMap ){
      pair.second->Print(); }
}

void PlotMerging::addSample( const std::string& name ) 
{
   _sampleMap.insert( sampleKey( name , new SampleInfo(name,_tupleDir) ) ); 
}

SampleInfo* PlotMerging::sample( const std::string& name )
{
   SampleMap::iterator it = _sampleMap.find(name);
   if( it == _sampleMap.end() ) { return NULL; }
   else return it->second; 
}

void PlotMerging::makeBasicPlots()
{
   for( const auto& pair : _sampleMap ) {
      pair.second->makeBasicPlots(); }
}

void PlotMerging::setLumi( const float x ){ _totalLumi = x ; }
