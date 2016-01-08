/*******************************************************************************
 *
 *  Filename    : CombineMgr_RunCommand.cc
 *  Description : Running the Higgs combine package from 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include <stdlib.h>

using namespace std;

void CombineMgr::RunCombine( const ChannelName& ch, const SampleName& massPoint, const string& method )
{
   ChannelMgr* channel = _channelList.at(ch);
   string cardfile = channel->cardFileName(massPoint);
   string limitfile = LimitFile(massPoint,method);
   char cmd[1024] ;

   sprintf( cmd , "( combine -M %s -m %s %s ; mv %s ./data/limits/ )&" , 
         method.c_str(),
         MassNumberString(massPoint).c_str(),
         cardfile.c_str(),
         limitfile.c_str() );
   
   cout << "Running Command ["<< cmd  <<"]" <<endl; 

   system( cmd );
}


int CombineMgr::MassNumber( const SampleName& massPoint )
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

string CombineMgr::MassNumberString( const SampleName& massPoint )
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

string CombineMgr::LimitFile( const SampleName& massPoint, const string& method )
{
   string limitfile 
      = "higgsCombineTest." + method + ".mH" + MassNumberString(massPoint) + ".root"; 
   return limitfile; 
}

