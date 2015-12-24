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
   cout << "Hello World! From RunMuon.out" << endl;

   cout << "Initializing Plot List...." << endl;
   initPlotList();
   cout << "Done!" << endl;

   cmbMgr = new CombineMgr( "MyOutput.root" );

   cmbMgr->SetCrossSections( "data/Common/CrossSection.asc" );
   cmbMgr->SetSampleWideWeights("data/Common/SampleWeights.acs");
   cmbMgr->SetSelectionEfficiency("data/MuonSignal/MuonSignal_SelectionEfficiencies.asc");
   cmbMgr->SetSampleInputs("data/MuonSignal/MuonSignal_files.asc");

   cmbMgr->makeBasicPlots();
   // cmbMgr->makeDataToBGPlot( ChiSquareTstarMass );
   // cmbMgr->makeDataToBGPlot( HitFitTstarMass );
   // cmbMgr->makeDataToBGPlot( ChiSquareTMass );
   // cmbMgr->makeDataToBGPlot( HitFitTMass );

   cmbMgr->makeInSampleComparison( Tstar_M0700 , HitFitTstarMass, ChiSquareTstarMass ); 
   cmbMgr->makeInSampleComparison( Tstar_M1000 , HitFitTstarMass, ChiSquareTstarMass ); 
   cmbMgr->makeInSampleComparison( Tstar_M1300 , HitFitTstarMass, ChiSquareTstarMass ); 
   cmbMgr->makeInSampleComparison( Tstar_M1600 , HitFitTstarMass, ChiSquareTstarMass ); 
   
   cmbMgr->makeInSampleComparison( Tstar_M0700 , HitFitTMass, ChiSquareTMass ); 
   cmbMgr->makeInSampleComparison( Tstar_M1000 , HitFitTMass, ChiSquareTMass ); 
   cmbMgr->makeInSampleComparison( Tstar_M1300 , HitFitTMass, ChiSquareTMass ); 
   cmbMgr->makeInSampleComparison( Tstar_M1600 , HitFitTMass, ChiSquareTMass ); 

   cmbMgr->Print();
   delete cmbMgr;
   return 0;
}
