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
//------------------------------------------------------------------------------ 
//   Helper variables
//------------------------------------------------------------------------------
static SampleInfo*  temp_sample;

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
PlotMerging::PlotMerging( const std::string& filename ) 
{
   _outputFile = new TFile( filename.c_str() , "RECREATE" );
   for( int i = 0 ; i < SAMPLE_NAME_COUNT ; ++i ){
      temp_sample = new SampleInfo( samplename[i] );
      _sampleMap[samplename[i]] = temp_sample ; 
   }
   InitSampleStyles();
   for( int i = 0 ; i < SAMPLE_NAME_COUNT ; ++i ){
      _sampleMap[samplename[i]]->makeBasicPlots(); 
   }
}

PlotMerging::~PlotMerging()
{
   for( auto sample : _sampleMap  ){ delete sample.second; }
   delete _outputFile;
}
