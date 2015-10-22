/*******************************************************************************
 *
 *  Filename    : GetPileUpWeight.cc
 *  Description : Simple ROOT MACROs for getting pile up weight
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#include "TFile.h"
#include "TDirectoryFile.h"
#include "TH1F.h"
#include <stdio.h>

static TFile*  Data_File;
static TFile*  MC_File; 
static TH1F*   Data_Hist;
static TH1F*   MC_Hist;
static TH1F*   weights;

void GetPileUpWeight()
{
   Data_File = new TFile( "./DataPileUp.root" );
   Data_Hist = (TH1F*)(Data_File->Get("pileup"));
   MC_File = new TFile( "./MCPileUp.root" );
   MC_Hist = (TH1F*)(MC_File->Get("demo/pileup"));

   Data_Hist->Scale( 1./ Data_Hist->Integral() );
   MC_Hist->Scale( 1./MC_Hist->Integral() );

   weights = (TH1F*)(Data_Hist->Clone());
   weights->Divide( MC_Hist );

   for( unsigned int i = 1 ; i < weights->GetNbinsX() +1 ; ++i ){
      printf( "[%u] %lf %lf %lf\n" 
            , i , MC_Hist->GetBinContent(i) , 
            Data_Hist->GetBinContent(i) , 
            weights->GetBinContent(i) ); 
   }

   puts( "const float PileUpWeight[60] = {\n" );
   for( unsigned int i = 1 ; i <= weights->GetNbinsX() ; ++i ){
      printf( "   %.8lf" , weights->GetBinContent(i));
      if( i != weights->GetNbinsX() ){ putchar(','); }
      if( i%5 == 0 ) {putchar('\n');}
   }
   puts( "};\n" );

   Data_Hist->Draw();
   MC_Hist->Draw("SAME");
}
