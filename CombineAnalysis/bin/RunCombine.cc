/*******************************************************************************
 *
 *  Filename    : RunMuon.cc
 *  Description : Highest level control flow for muon channel
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h" 
#include "TstarAnalysis/CombineAnalysis/interface/PlotDef.h"
#include <iostream>

using namespace std;

extern CombineMgr* cmbMgr;

void Usage();

int main( int argc, char* argv[] ) 
{
   if( argc != 2 ){
      cerr << "Error: Mismatch of required arguments" << endl;
      Usage();
      return -1;
   } 
   initPlotList();
   cmbMgr = new CombineMgr;
   cmbMgr->ParseCMDFile( argv[1] );

   return 0;
}

void Usage()
{
   cout << "./RunCombine <CMD filename>" << endl;
}


