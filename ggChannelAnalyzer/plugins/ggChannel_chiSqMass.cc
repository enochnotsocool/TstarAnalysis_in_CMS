/*******************************************************************************
 *
 *  Filename    : ggChannel_chiSqMass.cc
 *  Description : Computation of chi squared mass of t*
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *
*******************************************************************************/
#include "TstarAnalysis/ggChannelAnalyzer/interface/ggChannelAnalyzer.h"
#include "TLorentzVector.h"

//------------------------------------------------------------------------------ 
//   Defining constants
//------------------------------------------------------------------------------
#define TOP_MASS    173.34
#define TOP_WIDTH   2.00
#define W_MASS      80.385
#define W_WIDTH     2.085
#define TSTAR_WIDTH 10

//------------------------------------------------------------------------------ 
//   Helper static global variables
//------------------------------------------------------------------------------
static float tstarMass;
static float minChiSq;
static float trial_tstarMass;
static float trial_ChiSq;

static TLorentzVector  lepton;
static TLorentzVector  neutrino[2]; // Two candidate solution for nu
static std::vector<TLorentzVector> JetPermutation;
#define t_h_bjet     JetPermutation[0]
#define t_l_bjet     JetPermutation[1]
#define tstar_h_gjet JetPermutation[2]
#define tstar_l_gjet JetPermutation[3]
#define w_qjet1      JetPermutation[4]
#define w_qjet2      JetPermutation[5]
//------------------------------------------------------------------------------ 
//   Helper functions
//------------------------------------------------------------------------------
TLorentzVector solveNeutrino( const TLorentzVector& , float , float );

float ggChannelAnalyzer::computeChiSqMass()
{
   if( _selectedMuonList.size() == 1 ){
      const auto& muon = _selectedMuonList[0];
      lepton = TLorentzVector( muon->px(), muon->py() , muon->pz() , muon->energy() ) ;
   } else {
      const auto& elec = _selectedElecList[0];
      lepton = TLorentzVector( elec->px() , elec->py() , elec->pz() , elec->energy() );
   }
   solveNeutrino(lepton , MET_PT, MET_PHI );
   do{
      do{
         JetPermutation.clear();
         for( const auto& jet  : _selectedBJetList ){
            JetPermutation.push_back( TLorentzVector(jet->px(), jet->py() , jet->pz() , jet->energy() ) );
         }
         for( const auto& jet : _selectedLJetList ){
            if( JetPermutation.size() >= 6 ) { break; }
            JetPermutation.push_back( TLorentzVector(jet->px(), jet->py() , jet->pz() , jet->energy() ) );
         }
      }while(next_permutation( _selectedLJetList.begin() , _selectedBJetList.end() ));
   }while(next_permutation( _selectedBJetList.begin() , _selectedBJetList.end() ));
   return 0.0;
}


//------------------------------------------------------------------------------ 
//   Helper function implementations
//------------------------------------------------------------------------------
static float _alpha_ , _beta_    , _gamma_          ;
static float _a_     , _b_       , _c_       , _d_  ;
static float _lx_    , _ly_      , _lz_      , _lE_ ;
static float _npx_   , _npy_     , _npz_     , _nE_ ;
TLorentzVector solveNeutrino( const TLorentzVector& lep , float _MET_ , float _METPhi_ ) 
{
   _npx_    = _MET_ * cos( _METPhi_ )    ;
   _npy_    = _MET_ * sin( _METPhi_ )    ;

   _lx_     = lep.px()     ;
   _ly_     = lep.py()     ;
   _lz_     = lep.pz()     ;
   _lE_     = lep.Energy() ;
   
   _alpha_ = _npx_ + _lx_ ;
   _beta_  = _npy_ + _ly_ ;
   _gamma_ = W_MASS*W_MASS  - _MET_*_MET_ - _lE_*_lE_
      + _alpha_*_alpha_ + _beta_*_beta_ + _lz_*_lz_ ;

   _a_     =  4. *( _lE_*_lE_- _lz_*_lz_ ); 
   _b_     = -4. * _gamma_ * _lz_; 
   _c_     =  4. * _lE_*_lE_ * _MET_*_MET_ - _gamma_*_gamma_ ; 
   _d_     = _b_ * _b_ - 4. * _a_ * _c_;
   if( _d_ < 0 ) {
      _npz_ = -1. * _b_ / ( 2.*_a_ ) ;    
      _nE_  = sqrt( _npx_ * _npx_  + _npy_ * _npy_ + _npz_ * _npz_ ) ; 
      neutrino[0] = TLorentzVector( _npx_ , _npy_ , _npz_ , _nE_ ) ;
      neutrino[1] = neutrino[0];
   } else {
      _npz_ = ( -1. * _b_ + sqrt( _d_ ) )/ ( 2.*_a_ ) ;    
      _nE_  = sqrt(_npx_ * _npx_  + _npy_ * _npy_ + _npz_ * _npz_ ); 
      neutrino[0] = TLorentzVector( _npx_ , _npy_ , _npz_ , _nE_ ) ;
      _npz_ = ( -1. * _b_ - sqrt( _d_ ) )/ ( 2.*_a_ ) ;    
      _nE_  = sqrt( _npx_ * _npx_  + _npy_ * _npy_ + _npz_ * _npz_) ; 
      neutrino[1] = TLorentzVector( _npx_ , _npy_ , _npz_ , _nE_ ) ;
   }
}
