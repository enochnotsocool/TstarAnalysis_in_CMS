/*******************************************************************************
 *
 *  Filename    : Region.cc
 *  Description : Definition of regions 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : Here, we are only going to define the functions for the 
 *                dummy base class Region, for the definition of the 
 *                individual regions, read the file src/Region_*.cc
 *
 *
*******************************************************************************/
#include "TstarAnalysis/EventAnalyzer/interface/Region.h"

#include "TstarAnalysis/EventAnalyzer/interface/MiniEvent.h"

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
Region::Region(){}
Region::~Region(){}

//------------------------------------------------------------------------------ 
//   Data member interaction functions
//------------------------------------------------------------------------------
Region::pushback( const MiniEvent* x ){ _eventList.push_back( x ); } 
