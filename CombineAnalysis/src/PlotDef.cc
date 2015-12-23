/*******************************************************************************
 *
 *  Filename    : PlotDef.cc
 *  Description : Implementation of plotDef class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/PlotDef.h"
#include <stdio.h>
#include <cmath>

PlotDef::PlotDef() {}
PlotDef::~PlotDef(){}

void PlotDef::setBinCount( const unsigned int x ) { _binCount = x ; }
void PlotDef::setXMax( const float x ) { _xmax = x ; }
void PlotDef::setXMin( const float x ) { _xmin = x ; }
void PlotDef::setTitle( const std::string& x  ) {_title = x ; }
void PlotDef::setXtitle( const std::string& x ) { _xtitle = x ; }
void PlotDef::setYtitle( const std::string& x ) { _ytitle = x ; }

unsigned int PlotDef::BinCount() const { return _binCount; }
float        PlotDef::XMax() const { return _xmax ; }
float        PlotDef::XMin() const { return _xmin ; }
const std::string& PlotDef::Title() const { return _title; }
const std::string& PlotDef::Xtitle() const { return _xtitle; }
const std::string& PlotDef::Ytitle() const { return _ytitle; }

void PlotDef::makeYtitle( const std::string& unit )
{
   static char  buffer[1024];
   static float binWidth;
   binWidth = (_xmax-_xmin)/(float)_binCount ;
   if( fabs(binWidth-1.0)<0.0001){
      if( unit == "" ){
         sprintf( buffer , "Yield" );
      } else {
         sprintf( buffer , "Yield/%s" , unit.c_str() );
      }
   } else {
      if( unit == "" ){
         sprintf( buffer , "Yield/%0.2f" , binWidth );
      } else {
         sprintf( buffer , "Yield / (%0.2f %s)" , 
               binWidth , unit.c_str() );
      }
   }
   _ytitle = buffer;
}

