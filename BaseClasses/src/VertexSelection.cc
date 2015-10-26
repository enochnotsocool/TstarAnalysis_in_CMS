/*******************************************************************************
 *
 *  Filename    : VertexSelection.cc
 *  Description : Vertex Selection implementations
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#include "TH1F.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

bool isGoodPrimaryVertex( const reco::Vertex& v , TH1F* hist )
{
   if( hist!=NULL ) { hist->Fill(0); }
   if( v.isFake() ) { return false; }
   if( hist!=NULL ) { hist->Fill(1); }
   if( v.ndof() < 4 ) { return false; } 
   if( hist!=NULL ) { hist->Fill(2); }
   if( v.z() >=24 ) { return false; }
   if( hist!=NULL ) { hist->Fill(3); }
   if( v.position().Rho() >=2  ) { return false; }
   if( hist!=NULL ) { hist->Fill(4); }
   return true;
}


