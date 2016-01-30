/*******************************************************************************
 *
 *  Filename    : RunMuon.cc
 *  Description : Highest level control flow for muon channel
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/HistMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/SampleMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/SampleListing.h"
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include <iostream>

using namespace std;


extern CombineMgr* cmbMgr;

void Usage();

int main( int argc, char* argv[] ) 
{
   if( argc < 2 ){
      cerr << "Error: Mismatch of required arguments" << endl;
      Usage();
      return -1;
   }
   availablePlots.InitFromFile("./data/settings/define_plot.asc" );
   availableSamples.InitFromFile("./data/settings/define_sample.asc");
   cmbMgr = new CombineMgr;
   if( !cmbMgr->InitCommands() ){
      delete cmbMgr;
      return 1;
   }
   cmbMgr->RunInterface();

   delete cmbMgr;
   return 0;

}

void Usage()
{
   cout << "./RunCombine.out <CMD filename1> [CMD filename2...]" << endl;
}


