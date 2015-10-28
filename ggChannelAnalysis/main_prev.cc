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
#include "PlotMerging.h"

int main( int argc, char* argv[] ) 
{
   puts( "Hello World! This is the ggAnalysis Code!" );

   PlotMerging p( "output.root" );
   p.makePlot( "ChiSquareMass" );

   puts("GoodBye World! Hope I don't get segmentation fault!\n");
   return 0;
}

