/*******************************************************************************
 *
 *  Filename    : CombineMgr_MakeHiggsCombineFiles.cc
 *  Description : Implementation for making the Higgs combine files
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/NuisancePar.h"
#include "TFile.h"
#include "TH1F.h"
#include <string>

using namespace std;

void ChannelMgr::MakeLimitProcesses( vector<const HC_Process*>& processList  )
{
   // Making signal processes 
   HC_Process* signal = new HC_Process( _name , Tstar_M1000 ); 
   signal->SetShape( (TH1F*)_MCsignalMap[Tstar_M1000]->Hist( ChiSquareTstarMass )->Clone() );
   signal->SetRate( _MCsignalMap[Tstar_M1000]->getExpectedYield(_totalLumi).CentralValue() );
   NuisancePar lumi( "lumi" , "lnN" );
   signal->AddNuisance( lumi , 1.05 );
   processList.push_back( signal );

   // Making Background process 
   const PlotDef& def = availiablePlots[ChiSquareTMass];
   double totalbg = 0;
   TH1F* bg = new TH1F( "bg", "bg" , def.BinCount() , def.XMin() , def.XMax() );
   for( const auto& sample: _MCbackgroundMap ){
      bg->Add( sample.second->Hist( ChiSquareTstarMass ), getHistScale( sample.second ) );
      totalbg += sample.second->getExpectedYield( _totalLumi ).CentralValue(); 
   }

   HC_Process* bgprocess = new HC_Process( _name , TTJets );
   bgprocess->SetShape( (TH1F*)bg->Clone() );
   bgprocess->SetRate( totalbg );
   processList.push_back( bgprocess );
}

