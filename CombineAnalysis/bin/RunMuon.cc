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

int main( int argc, char* argv[] ) 
{
   cout << "Hello World!" << endl;
   cmbMgr = new CombineMgr( "MyOutput.root" );

   cmbMgr->SetCrossSections( "data/CrossSection.asc" );
   cmdMgr->SetSampleWideWeights("data/SampleWeights.acs");
   cmbMgr->SetSelectionEfficiency("data/MuonSignal_SelectionEfficiencies.asc");
   cmbMgr->SetSampleInputs("data/MuonSignal_files.asc");

   cmbMgr->Print();
   delete cmbMgr;
   return 0;
}
