/*******************************************************************************
 *
 *  Filename    : PlotCreate.cc
 *  Description : Implementation for plot merging
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "PlotMerging.h"
#include <stdio.h>
#include <iostream>
//------------------------------------------------------------------------------ 
//   Helper variables
//------------------------------------------------------------------------------
SampleInfo* tempSample;
TH1F*       tempHist; 
float       tempScale;

void PlotMerging::makePlot( const std::string& target )
{

   printf( "making plot %s\n" , target.c_str() );
   _canvas    = new TCanvas( target.c_str() , target.c_str() );
   _stackHist = new THStack( target.c_str() , target.c_str() );

   // Plotting MC samples 
   for( const auto& pair : _sampleMap ) {
      if( pair.first == "Data" ) continue;  // Skipping data
      tempSample  = pair.second ; 
      tempHist    = (TH1F*)(tempSample->Hist( target )->Clone());
      tempScale   = _totalLumi * tempSample->crossSection() ;
      tempScale  *= tempSample->selectionEff();
      tempScale  /= tempHist->Integral();
      tempHist->Scale( tempScale ) ; 
      _stackHist->Add( tempHist ); 
      printf( "Plotting sample %s with %f events\n", pair.first.c_str(), tempScale );
   }
   _stackHist->Draw("HIST AE");

   //----- Plotting data  ---------------------------------------------------------
   if( ! sample("Data") ){
      std::cerr << "Warning! Data sample not found!" << std::endl; 
   }else{
      sample("Data")->Hist(target)->SetMarkerStyle(21);
      sample("Data")->Hist(target)->Draw("SAME LPE1");
   }

   printf("Writing to canvas....");
   _canvas->Write();
   delete _stackHist;
   delete _canvas;
   printf("Done!\n");
}
