/*******************************************************************************
 *
 *  Filename    : HC_Process.cc
 *  Description : HC Process implementation functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/HC_Process.h"

using namespace std;

HC_Process::HC_Process( const std::string& ch , const std::string& sample ):
   _channelName(ch),
   _processName(sample),
   _shape_hist(NULL),
   _rate(0)
{
}

HC_Process::~HC_Process()
{
   if( _shape_hist != NULL ) { delete _shape_hist; }
}

void HC_Process::Noramlize()
{
   _shape_hist->Scale( _rate / _shape_hist->Integral() );
}

