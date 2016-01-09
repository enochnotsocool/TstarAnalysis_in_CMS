/*******************************************************************************
 *
 *  Filename    : ChannelMgr_RunCommand.cc
 *  Description : Running the Higgs combine package from 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include <stdlib.h>

using namespace std;

void ChannelMgr::RunCombine( const SampleName& massPoint, const string& method )
{
   const string cardfile   = cardFileName(massPoint);
   const string raw_path   = raw_combineoutput(massPoint,method);
   const string store_path = store_combineoutput(massPoint,method);
   char cmd[1024] ;

   sprintf( cmd , "( combine -M %s -m %s %s &> /dev/null ; mv %s %s )&" , 
         method.c_str(),
         MassNumberString(massPoint).c_str(),
         cardfile.c_str(),
         raw_path.c_str(),
         store_path.c_str() );
   
   cout << "Running Command ["<< cmd  <<"]" <<endl; 
   system( cmd );
}


int ChannelMgr::MassNumber( const SampleName& massPoint ) const
{
   if( massPoint == Tstar_M0700 ) { return 700; }
   if( massPoint == Tstar_M0800 ) { return 800; }
   if( massPoint == Tstar_M0900 ) { return 900; }
   if( massPoint == Tstar_M1000 ) { return 1000; }
   if( massPoint == Tstar_M1100 ) { return 1100; }
   if( massPoint == Tstar_M1200 ) { return 1200; }
   if( massPoint == Tstar_M1300 ) { return 1300; }
   if( massPoint == Tstar_M1400 ) { return 1400; }
   if( massPoint == Tstar_M1500 ) { return 1500; }
   if( massPoint == Tstar_M1600 ) { return 1600; }
   return -1;
}

string ChannelMgr::MassNumberString( const SampleName& massPoint )const
{
   if( massPoint == Tstar_M0700 ) { return "700" ; }
   if( massPoint == Tstar_M0800 ) { return "800" ; }
   if( massPoint == Tstar_M0900 ) { return "900" ; }
   if( massPoint == Tstar_M1000 ) { return "1000" ; }
   if( massPoint == Tstar_M1100 ) { return "1100" ; }
   if( massPoint == Tstar_M1200 ) { return "1200" ; }
   if( massPoint == Tstar_M1300 ) { return "1300" ; }
   if( massPoint == Tstar_M1400 ) { return "1400" ; }
   if( massPoint == Tstar_M1500 ) { return "1500" ; }
   if( massPoint == Tstar_M1600 ) { return "1600" ; }
   return ""                                    ;
}

string ChannelMgr::raw_combineoutput( const SampleName& massPoint, const string& method ) const
{
   string ans  
      = "higgsCombineTest." + method + ".mH" + MassNumberString(massPoint) + ".root"; 
   return ans; 
}

string ChannelMgr::store_combineoutput( const SampleName& massPoint, const string& method ) const
{
   string ans 
      = "./data/limits/" + Stringify(_name) + "_" + MassNumberString(massPoint) + "_" + method + ".root";
   return ans;
}
