/*******************************************************************************
 *
 *  Filename    : VertexSelection.cc
 *  Description : Vertex Selection implementations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#include "TstarAnalysis/BaseClasses/interface/Utils.h"
#include "TstarAnalysis/BaseClasses/interface/ObjectSelection.h"

bool ObjectSelection::isGoodPrimaryVertex( const reco::Vertex& v , TH1F* hist ) const
{
   int i = 0;
   FillHistAtBin( hist , i );
   if( v.isFake() ) { return false; }
   FillHistAtBin( hist , i );
   if( v.ndof() < fVertex_Minimum_DegreeOfFreedom ) { return false; } 
   FillHistAtBin( hist , i );
   if( v.z() >= fVertex_Maximum_Z ) { return false; }
   FillHistAtBin( hist , i );
   if( v.position().Rho() >= fVertex_Maximum_Rho  ) { return false; }
   return true;
}


