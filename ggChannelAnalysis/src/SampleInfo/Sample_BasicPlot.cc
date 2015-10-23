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

void SampleInfo::makeBasicPlots()
{
   printf( "Making basic plots for %s\n", _name.c_str() );
  
   SetInputTree( _chain );
   for( int i = 0 ; i < _chain->GetEntries() ; ++i ){
   void makeJetPtPlot();
      _chimass->Fill( EventBranches._chiMass , getStatisticsWeight() );
      for( size_t i = 0 ; i < JetBranches._VecList.size() ; ++i ){
         _jetPt->Fill( JetBranches._VecList[i].Pt() , getStatisticsWeight() );
      }
   }
}


