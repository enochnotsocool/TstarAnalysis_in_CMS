/*******************************************************************************
 *
 *  Filename    : Sample_BasicPlot.cc
 *  Description : Implementation of basic plots 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "SampleInfo.h"
#include "MiniEventBranches.h"
#include "ParticleReader.h"

void SampleInfo::makeChiMassPlot()
{
   printf( "Making chimass plot for %s\n" , _name.c_str() );
   SetInputTree( _chain );
   for( size_t i = 0 ; i < _chain->GetEntries() ; ++i ){
      _chain->GetEntry(i);
      _chimass->Fill( EventBranches._chiMass ); 
   }
}
