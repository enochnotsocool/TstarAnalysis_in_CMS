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

//------------------------------------------------------------------------------ 
//   Constructor and desctructor
//------------------------------------------------------------------------------
SampleInfo::SampleInfo( const std::string& name ) 
{
   _name = name ;
   _targetEventCount = DONT_APPLY_WEIGHT ;
   _chain   = new TChain( "ggChannelProcessor/EventVariables" );

   addHist( "ChiMass" , 50 , 0 , 2000 );
   addHist( "JetPt"   , 50 , 0 , 600  );
}

SampleInfo::~SampleInfo()
{
   for( auto hist_pair : _histMap ){
      delete hist_pair.second;
   }
}

//------------------------------------------------------------------------------ 
//   Basic access function
//------------------------------------------------------------------------------
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
   if( _targetEventCount <= DONT_APPLY_WEIGHT ) { 
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

TH1F* SampleInfo::Hist( const std::string& histname )
{
   return _histMap[histname];
}

void SampleInfo::setFillColor( const Color_t c , const float alpha )
{
   for( auto histpair : _histMap ){
      histpair.second->SetFillColorAlpha( c , alpha );
   }
}

void SampleInfo::setLineColor( const Color_t c )
{
   for( auto histpair : _histMap ){
      histpair.second->SetLineColor( c  );
   }
}

void SampleInfo::addPlotStyle( const std::string& x )
{
   _plotstyle += x ;
}
void SampleInfo::HistPlot( const std::string& name , const std::string& style )
{
   _histMap[name]->Draw( style.c_str() );
}

//------------------------------------------------------------------------------ 
//   Private member functions
//------------------------------------------------------------------------------
void SampleInfo::addHist( const std::string& histname , int nbin , float xmin , float xmax )
{
   TH1F* temp = new TH1F( (_name+histname).c_str() , (_name+histname).c_str() , nbin , xmin , xmax );
   _histMap[ histname ] = temp ;
}
