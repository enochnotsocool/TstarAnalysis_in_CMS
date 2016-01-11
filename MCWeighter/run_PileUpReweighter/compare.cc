#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"

void compare() 
{
   TFile* dataFile = TFile::Open( "DataPileUp.root" );
   TFile* mcFile   = TFile::Open( "MCPileUp.root" );
   TFile* output   = new TFile( "PileUpCompare.root", "RECREATE" );
   TCanvas*      c = new TCanvas( "PileUpCompare" , "PileUpCompare" );
   TLegend*      l = new TLegend( 0.75 , 0.75 , 0.95 , 0.95 );
   TH1F*  dataHist = (TH1F*)(dataFile->Get("pileup"));
   TH1F*  mcHist   = (TH1F*)(mcFile->Get("demo/pileup"));

   float dataFactor;
   float mcFactor;
   float rescaleFactor; 
   
   dataHist->Scale( 1./ dataHist->Integral() ) ;
   mcHist->Scale( 1./ mcHist->Integral() );

   for( int i = 1 ; i <= 50 ; ++i ) {
      dataFactor = dataHist->GetBinContent( i ); 
      mcFactor   = mcHist->GetBinContent(i);
      rescaleFactor = dataFactor/mcFactor; 
      if( rescaleFactor < 0.000001 ) rescaleFactor = 0. ; 
            printf( "if( x == %2d ) { return  %.12f ; } //  : %.12f/%.12f\n" , 
            i-1 , rescaleFactor , 
            dataFactor , mcFactor );
   }

   // Drawing commands
   dataHist->SetTitle("Comparison of Pile Up");
   dataHist->GetXaxis()->SetTitle( "Number of true interactions" );
   dataHist->GetYaxis()->SetTitle( "Normalized Yield" );
   dataHist->SetMarkerStyle(21);
   dataHist->SetStats(0);
   dataHist->SetLineColor( kBlack ); 

   mcHist->SetFillColor( kBlue+2 );
   mcHist->SetFillStyle( 3004 );

   l->AddEntry( dataHist , "Data" , "pl" );
   l->AddEntry( mcHist   , "Monte Carlo" , "f" );

   dataHist->Draw();
   mcHist->Draw("SAME" );
   l->Draw();
   
   c->Write();
}
