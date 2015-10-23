/*******************************************************************************
 *
 *  Filename    : main.cc
 *  Description : Main control flow 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  As of writing, there is not yet a motivation to make program interactive
 *
*******************************************************************************/
#include <stdio.h>
#include "TFile.h"
#include "THStack.h"
#include "TCanvas.h"

#include "SampleDef.h"
int main( int argc, char* argv[] ) 
{
   puts( "Hello World! This is the ggAnalysis Code!" );
   InitSamples();
   Tstar_Signal.makeBasicPlots();
   TTJets_background.makeBasicPlots();
   Data.makeBasicPlots();
   
   TFile* output = new TFile( "output.root" , "RECREATE" );
   TCanvas* c1 = new TCanvas( "c1" , "c1" , 600 , 600 );
   THStack* chiMassPlot = new THStack( "chimassStack" ,  "chimass" );
   chiMassPlot->Add( TTJets_background.Hist("ChiMass"));
   chiMassPlot->Add( Tstar_Signal.Hist("ChiMass"));

   chiMassPlot->Draw();
   Data.HistPlot("ChiMass", "SAMEPE");
   c1->Write();
   output->Write();

   puts("GoodBye World! Hope I don't get segmentation fault!\n");
   return 0;
}

