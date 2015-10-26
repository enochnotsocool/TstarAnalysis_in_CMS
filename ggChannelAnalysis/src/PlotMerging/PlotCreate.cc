/*******************************************************************************
 *
 *  Filename    : PlotCreate.cc
 *  Description : Implementation for plot merging
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "PlotMerging.h"
#include "stdio.h"
void PlotMerging::makePlot( const std::string& target )
{

   printf( "making plot %s\n" , target.c_str() );
   _canvas = new TCanvas( target.c_str() , target.c_str() );
   _stackHist = new THStack( target.c_str() , target.c_str() );

   // Starting from 1, skipping over data 
   for( int i = SAMPLE_NAME_COUNT-1 ; i > 0 ; --i ){
      _stackHist->Add( _sampleMap[samplename[i]]->Hist(target) );
   }
   _stackHist->Draw("HIST AE");
   _sampleMap["Data"]->Hist(target)->SetMarkerStyle(21);
   _sampleMap["Data"]->Hist(target)->Draw("SAME LPE1");

   printf("Writing to canvas....");
   _canvas->Write();
   delete _stackHist;
   delete _canvas;
   printf("Done!\n");
}
