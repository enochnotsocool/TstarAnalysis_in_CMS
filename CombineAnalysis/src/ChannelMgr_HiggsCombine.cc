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
   HC_Process* m700  = new HC_Process( _name , Tstar_M0700 );
   HC_Process* m1000 = new HC_Process( _name , Tstar_M1000 );
   HC_Process* m1300 = new HC_Process( _name , Tstar_M1300 );
   HC_Process* m1600 = new HC_Process( _name , Tstar_M1600 );
   
   makeSignalProcess( m700 );
   makeSignalProcess( m1000 );
   makeSignalProcess( m1300 );
   makeSignalProcess( m1600 );

   processList.push_back( m700 );
   processList.push_back( m1000 );
   processList.push_back( m1300 );
   processList.push_back( m1600 );

   // Making Background process 
   HC_Process* ttjets  = new HC_Process( _name, TTJets );
   HC_Process* singlet = new HC_Process( _name, SINGLE_T );
   HC_Process* bosons  = new HC_Process( _name, BOSONS );
   HC_Process* ttBoson = new HC_Process( _name, TT_PLUS_BOSON );

   makeBGLimitProcess( ttjets, TTJets, TTJets);
   makeBGLimitProcess( singlet, SingleT_S, SingleTbar_TW );
   makeBGLimitProcess( bosons , WJets, ZZ );  
   makeBGLimitProcess( ttBoson, TTW_Lepton, TTZ_Quark ); 

   processList.push_back( ttjets );
   processList.push_back( singlet );
   processList.push_back( bosons );
   processList.push_back( ttBoson );
}

void ChannelMgr::makeBGLimitProcess( HC_Process* const proc, const SampleName& first, const SampleName& last)
{
   const PlotDef& def = availiablePlots[ChiSquareTstarMass];
   const string  name = Stringify(proc->GetChannel()) +"_" + Stringify(proc->GetProcess()) ;
   TH1F* temp = NULL;
   Parameter totalbg;
   double scale = 0.0;

   proc->SetShape( new TH1F( name.c_str(), name.c_str() , def.BinCount() , def.XMin() , def.XMax() ) );
   
   for( auto it= _MCbackgroundMap.find( first ); it!=_MCbackgroundMap.end() && it->first <= last ; ++it ){
      temp = it->second->Hist( ChiSquareTstarMass );
      if( temp->Integral() != 0 ){
         scale = getHistScale( it->second );
         proc->GetShape()->Add( temp, scale );
         totalbg+= it->second->getExpectedYield( _totalLumi );
         cout << name << " " << totalbg << endl; 
      }
   }
   proc->SetRate( totalbg.CentralValue() );
   normalizeProcessShape( proc );
   
   //------------------------------------------------------------------------------ 
   //   Setting Nuisance parameters
   //------------------------------------------------------------------------------
   NuisancePar norm( (name+"_Norm").c_str() , "lnN" );
   proc->AddNuisance( norm , 1 + totalbg.RelativeAvgError() );
   
   NuisancePar lumi( "lumi" , "lnN" );
   proc->AddNuisance( lumi , 1.05 );
}

void ChannelMgr::makeSignalProcess( HC_Process* const proc )
{
   const SampleMgr* const sample = _MCsignalMap.at( proc->GetProcess() );
   proc->SetShape( (TH1F*)sample->Hist( ChiSquareTstarMass )->Clone() );
   proc->SetRate( sample->getExpectedYield(_totalLumi).CentralValue() );
   normalizeProcessShape( proc );
   NuisancePar lumi( "lumi" , "lnN" );
   proc->AddNuisance( lumi , 1.05 );
}

void ChannelMgr::normalizeProcessShape( HC_Process* const proc )
{
   proc->GetShape()->Scale( proc->GetRate() / proc->GetShape()->Integral() );
}
