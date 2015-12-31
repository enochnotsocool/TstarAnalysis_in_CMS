/*******************************************************************************
 *
 *  Filename    : RunMuon.cc
 *  Description : Highest level control flow for muon channel
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h" 
#include <iostream>

using namespace std;

extern CombineMgr* cmbMgr;

void Usage();

int main( int argc, char* argv[] ) 
{
   if( argc != 3 ){
      cerr << "Error: Mismatch of required arguments" << endl;
      Usage();
      return -1;
   } 
   cmbMgr = new CombineMgr;
   return 0;
}

void Usage()
{
   cout << "./RunCombine <Output filename> <CMD filename>" << endl;
}


