/*******************************************************************************
 *
 *  Filename    : make_settings.cc
 *  Description : Simple program file for making the settings configurations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#include "CMSSW_Utils/Utils_Functions/interface/Utils.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "TH1F.h"
#include "TFile.h"

using namespace std;
   
const string cmssw_base = getenv( "CMSSW_BASE" );
const string hist_base  = cmssw_base + "/src/TstarAnalysis/Filters/data/HISTOGRAMS/";

string sampleName( const string& );

int main(int argc, char *argv[])
{
   cout << cmssw_base << endl;
   cout << hist_base << endl;
   
   if( argc != 2 ){
      cout << "Please input channel!" << endl;
      cout << "Avaliable" << endl;
      vector<string> channellist = ListDir( hist_base );
      for( const auto& ch : channellist ){
            cout << ch << endl;
      }
      return 1;
   }

   const string channel = argv[1];
   const vector<string>  sampleList = ListDir( hist_base + channel );
   FILE* setting = fopen( (channel+"selection.txt").c_str() , "w"  );
   for( const auto& sample : sampleList ){
      const string shortname = sampleName( sample );
      if( sample.front() == '.' ) { continue; }
      if( shortname == "" ) { continue; }

      cout << "Running sample: " << sample << endl;
      const string sampledir = hist_base+channel+"/"+sample;
      TH1F* sampleTotal = new TH1F( "total" , "total" , 10 , 0 , 10 );
      const vector<string> filelist = ListFiles( sampledir );

      for( const auto& filename : filelist ){
         
         cout << "\r\tRunning on file " << filename << flush; 
         
         const string filepath = sampledir + "/" + filename ;
         TFile* file = TFile::Open( filepath.c_str() );
         if( file->IsZombie() ){ continue; }
         TH1F* temp = (TH1F*)file->Get("myFilter/EventSelection" );
         if( temp ){
            sampleTotal->Add( temp );
         }
         file->Close();
      }
      
      double eff = sampleTotal->GetBinContent(7) / sampleTotal->GetBinContent(1);
      double err = sqrt( eff*(1-eff)/sampleTotal->GetBinContent(1) );

      cout << "Done!" << endl 
           << "\tIntegral:   " << sampleTotal->Integral() << endl
           << "\tEfficiency: " << eff << endl
           << "\tError:      " << err << endl;
      fprintf( setting , "%-15s %.12lf %.12lf\n" , shortname.c_str() , eff, err  );
      delete sampleTotal;
   }
   fclose( setting );
   return 0;
}

string sampleName( const string& cmssw_name )
{
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M1000"; }
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M1100"; }
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M1200"; }
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M1300"; }
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M1400"; }
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M1500"; }
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M1300"; }
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M0700"; }
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M0800"; }
   if( cmssw_name == "TstarTstarToTgluonTgluon_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "Tstar_M0900"; }

   if( cmssw_name == "TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v3"){return "TTJets"; }
   if( cmssw_name == "ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "SingleT_S"; }
   if( cmssw_name == "ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "SingleT_T"; }
   if( cmssw_name == "ST_tW_antitop_5f_DS_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "SingleTbar_TW"; }
   if( cmssw_name == "ST_tW_top_5f_DS_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "SingleT_TW"; }

   if( cmssw_name == "WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "WJets_HT100_200"; }
   if( cmssw_name == "WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "WJets_HT200_400"; }
   if( cmssw_name == "WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "WJets_HT400_600"; }
   if( cmssw_name == "WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "WJets_HT600_800"; }
   if( cmssw_name == "WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "WJets_HT800_1200"; }
   if( cmssw_name == "WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "WJets_HT1200_2500"; }
   if( cmssw_name == "WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "WJets_HT2500_Inf"; }

   if( cmssw_name == "DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "ZJets_HT100_200"; }
   if( cmssw_name == "DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "ZJets_HT200_400"; }
   if( cmssw_name == "DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2"){return "ZJets_HT400_600"; }
   if( cmssw_name == "DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "ZJets_HT400_Inf"; }

   if( cmssw_name == "TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "TTW_Quark"; }
   if( cmssw_name == "TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "TTZ_Quark"; }
   if( cmssw_name == "TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "TTZ_Quark"; }
   if( cmssw_name == "TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2"){return "TTZ_Lepton"; }

   if( cmssw_name == "WW_TuneCUETP8M1_13TeV-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "WW"; }
   if( cmssw_name == "WZJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "WZ"; }
   if( cmssw_name == "ZZ_TuneCUETP8M1_13TeV-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"){return "ZZ"; }
   return ""  ; 
}



