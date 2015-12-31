/*******************************************************************************
 *
 *  Filename    : HC_Process.cc
 *  Description : HC Process implementation functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/HC_Process.h"

using namespace std;

HC_Process::HC_Process( const ChannelName x, const SampleName y)
{
   _channelName = x;
   _processName = y; 
}
HC_Process::~HC_Process(){}

ChannelName HC_Process::GetChannel() const { return _channelName; }
SampleName  HC_Process::GetProcess() const { return _processName; }
string HC_Process::ObjName() const 
{
   return Stringify(_channelName)+"_"+Stringify(_processName);
}

void    HC_Process::SetShape( TH1F* x ) { _shape_hist = x ; }
TH1F*   HC_Process::GetShape() const { return _shape_hist; }
void    HC_Process::SetRate( double x ) { _rate = x ; }
double  HC_Process::GetRate() const { return _rate; }
void    HC_Process::AddNuisance( const NuisancePar& x , float y ) { _nuisance[x] = y; }
NuisanceMap& HC_Process::GetNuisance() { return _nuisance; }
const NuisanceMap& HC_Process::GetNuisance() const { return _nuisance; }

bool HC_Process::operator==( const HC_Process& x ) const 
{
   if( _channelName == x._channelName ) { 
      if( _processName == x._processName ){
         return true;
      }
      return false;
   }
   return false;
}

bool HC_Process::operator<( const HC_Process& x ) const
{
   if( _channelName < x._channelName ) { return true; }
   if( _channelName > x._channelName ) { return false; }
   if( _processName < x._processName ) { return true; }
   return false;
}
bool HC_Process::operator>( const HC_Process& x ) const
{
   if( _channelName > x._channelName ) { return true; }
   if( _channelName < x._channelName ) { return false; }
   if( _processName > x._processName ) { return true; }
   return false;
}

