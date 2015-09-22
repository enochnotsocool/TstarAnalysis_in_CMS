/***************************************************************************************************
 *
 *  Filename    : Region_AA_Signal.cc
 *  Description : Region definition for gamma gamma Channel signal region
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *
***************************************************************************************************/

#include "TstarAnalysis/EventAnalyzer/interface/Region.h"

//-------------------------------------------------------------------------------------------------- 
//   Constructor and destructor
//-------------------------------------------------------------------------------------------------- 
AA_Signal::AA_Signal()  {}
AA_Signal::~AA_Signal() {} 

//-------------------------------------------------------------------------------------------------- 
//   Virtual functions 
//--------------------------------------------------------------------------------------------------
bool AA_Signal::isRegionEvent( const MiniEvent* )  const 
{
   return true;
}

void AA_Signal::processEvent( const MiniEvent* )
{
   
}

void AA_Signal::process( ) 
{
   
}
