/*******************************************************************************
 *
 *  Filename    : BaseFilter.cc
 *  Description : Implementation for base filter class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/BaseFilter/interface/BaseFilter.h"

typedef std::vector<reco::Vertex>  VertexList;
typedef VertexList::const_iterator VertexListCIT;

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
BaseFilter::BaseFilter( const edm::ParameterSet& iConfig ):
   MiniAODFilter( iConfig )
{

}

BaseFilter::~BaseFilter(){}

void BaseFilter::beginJob() {}
void BaseFilter::endJob(){}

//------------------------------------------------------------------------------ 
//   Processing particle collection to storages classes
//------------------------------------------------------------------------------
void BaseFilter::processVertex()
{ 
   bool gotPV = false;
   VertexListCIT vertex;
   for( vertex = _vertexList->begin() ; vertex != _vertexList->end() ; vertex++ ){
      if( !gotPV && isGoodPrimaryVertex( *vertex,0 ) ){
         _primaryVertex = *vertex ;
         gotPV = true;
         break;
      }
   }
}

void BaseFilter::processMuon(){}
void BaseFilter::processElectron(){}
void BaseFilter::processJet(){}

//------------------------------------------------------------------------------ 
//   Selection Criteria 
//------------------------------------------------------------------------------
#define HIST_COUNT( N ) if( hist!=0 ){ hist->Fill(N); }
bool BaseFilter::passEventSelection( TH1F* hist=0 )
{ 
   return false;
}

//----- Vertex Selection  ------------------------------------------------------
bool BaseFilter::isGoodPrimaryVertex( const reco::Vertex& v , TH1F* hist=0 )
{
   HIST_COUNT(0);
   if( v.isFake() ) { return false; }
   HIST_COUNT(1);
   if( v.ndof() < 4 ) { return false; } 
   HIST_COUNT(2);
   if( v.z() >=24 ) { return false; }
   HIST_COUNT(3);
   if( v.position().Rho() >=2  ) { return false; }
   HIST_COUNT(4);
   return true;
}

//----- Muon Selection  -------------------------------------------------------
bool BaseFilter::isSelectionMuon( const pat::Muon& mu , const reco::Vertex& pv , TH1F* hist=0 )
{ 
   HIST_COUNT(0);
   if( !muon::isTightMuon( mu, pv ) ) { return false; }
   HIST_COUNT(1);
   if( mu.pt()        < 30 ) { return false ; }
   HIST_COUNT(2);
   if( abs(mu.eta())  > 2.1) { return false ; }
   HIST_COUNT(3);
   if( mu.trackIso() / mu.pt() > 0.05 ) { return false ; }
   HIST_COUNT(4);
   return true; 
}
bool BaseFilter::isVetoMuon( const pat::Muon& mu , TH1F* hist=0 )
{
   HIST_COUNT(0);
   if( !muon::isLooseMuon( mu ) ){ return false; } 
   HIST_COUNT(1);
   if( mu.pt() < 15 ) { return false; }
   HIST_COUNT(2);
   if( abs( mu.eta() ) < 2.4 ) { return false; } 
   HIST_COUNT(3);
   if( mu.trackIso() /mu.pt()  > 0.1 ) { return false; }
   HIST_COUNT(4);
   return true;
}

//----- Electron Selectoin  ----------------------------------------------------
bool BaseFilter::isSelectionElectron( const pat::Electron& el , const edm::ValueMap<bool> , TH1F* hist=0 )
{
   HIST_COUNT(0);
   // MEDIUM ELECTRON FLAG
   HIST_COUNT(1);
   if( el.pt() < 30 ) { return false; }
   HIST_COUNT(2);
   if( abs(el.eta()) > 2.1 ) { return false; } 
   HIST_COUNT(3);
   if( abs(el.eta()) > 1.44 && abs(el.eta()) < 1.57 ){ return false ; }
   HIST_COUNT(4);
   return true;
}
bool BaseFilter::isVetoElectron( const pat::Electron& el , const edm::ValueMap<bool> , TH1F* hist=0 )
{
   HIST_COUNT(0);
   // LOOSE ELECTRON FLAG
   HIST_COUNT(1);
   if( el.pt() < 15 ) { return false; }
   HIST_COUNT(2);
   if( abs(el.eta()) > 2.4 ) { return false; } 
   HIST_COUNT(3);
   if( abs(el.eta()) > 1.44 && abs(el.eta()) < 1.57 ){ return false ; }
   HIST_COUNT(4);
   return true;
}

//----- Jet Selection  ---------------------------------------------------------
bool BaseFilter::isSelectionJet( const pat::Jet& , const MuonList& , const ElectronList& , TH1F* hist=0)
{
   return true;
}

DEFINE_FWK_MODULE( BaseFilter );

