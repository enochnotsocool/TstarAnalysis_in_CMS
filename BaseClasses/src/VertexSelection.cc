/*******************************************************************************
 *
 *  Filename    : VertexSelection.cc
 *  Description : Vertex Selection implementations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#include "TH1F.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

bool isGoodPrimaryVertex( const reco::Vertex& v , TH1F* )
{
   if( v.isFake() ) { return false; }
   if( v.ndof() < 4 ) { return false; } 
   if( v.z() >=24 ) { return false; }
   if( v.position().Rho() >=2  ) { return false; }
   return true;
}


