/*******************************************************************************
 *
 *  Filename    : SampleInfo.cc
 *  Description : Implementations of files
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "SampleInfo.h"
#include <stdio.h>
#define DONT_APPLY_WEIGHT  -1

SampleInfo::SampleInfo( const std::string& name ) 
{
   _name = name ;
   _targetEventCount = DONT_APPLY_WEIGHT ;
   _chain   = new TChain( "ggChannelAnalyzer/EventVariables" );
   _chimass = new TH1F( (_name+"chiMass").c_str() , (_name+"chiMass").c_str() , 50 , 0 , 2000 );
}

SampleInfo::~SampleInfo(){}

void SampleInfo::addFile( const std::string& filename )
{
   printf("Adding file %s to %s\n" , filename.c_str() , _name.c_str() );
   _chain->Add( filename.c_str() );
}


void SampleInfo::setTargetEventCount( const float x )
{
   _targetEventCount = x;
}

float SampleInfo::getStatisticsWeight() const
{
   static float actualEventCount; 
   if( _targetEventCount < DONT_APPLY_WEIGHT ) { 
      return 1.; }
   actualEventCount = (float)_chain->GetEntries();
   return _targetEventCount / actualEventCount ;
}

void SampleInfo::setPlotStyle( const std::string& x )
{
   _plotstyle = x ;
}

const std::string& SampleInfo::plotStyle() const 
{
   return _plotstyle;
}

TH1F* SampleInfo::chimassHist() { return _chimass; }
