/*******************************************************************************
 *
 *  Filename    : PlotDef.cc
 *  Description : Implementation of plotDef class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "PlotDef.h"

PlotDef::PlotDef() {}
PlotDef::~PlotDef(){}

void PlotDef::setBinCount( const unsigned int x ) { _binCount = x ; }
void PlotDef::setXMax( const float x ) { _xmax = x ; }
void PlotDef::setXMin( const float x ) { _xmin = x ; }
void PlotDef::setXtitle( const std::string& x ) { _xtitle = x ; }
void PlotDef::setYtitle( const std::string& x ) { _ytitle = x ; }

unsigned int PlotDef::BinCount() const { return _binCount; }
float        PlotDef::XMax() const { return _xmax ; }
float        PlotDef::XMin() const { return _xmin ; }
const std::string& PlotDef::Xtitle() const { return _xtitle; }
const std::string& PlotDef::Ytitle() const { return _ytitle; }

