/*******************************************************************************
 *
 *  Filename    : Utils.cc
 *  Description : Implementation of Utils functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TH1F.h"
#include "TLorentzVector.h"
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"

using namespace std;

void FillHistAtBin( TH1F* hist , int& counter )
{
   if( hist != NULL ){ hist->Fill( counter ); }
   ++counter;
}

ostream& operator<<( ostream& os , const TLorentzVector& x )
{
   os << "(" << x.Pt() << ", " << x.Eta() << ", " 
      << x.Phi() << ", " << x.Energy() << ")";
   return os;
}

TLorentzVector ToRootFormat( const math::XYZTLorentzVector& x )
{
   TLorentzVector ans;
   ans.SetPtEtaPhiE( x.pt(), x.eta(), x.phi(), x.energy() );
   return ans;
}
