/*******************************************************************************
 *
 *  Filename    : ggChannel_chiSqMass.cc
 *  Description : Computation of chi squared mass of t*
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *
*******************************************************************************/
#include "TstarAnalysis/ggChannelAnalyzer/interface/ggChannelAnalyzer.h"
#include "TstarAnalysis/ggChannelAnalyzer/interface/JetPermutator.h"
#include "TLorentzVector.h"
#include <iostream>

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
static float trial_ChiSq;

static TLorentzVector w_qq;
static TLorentzVector w_ln;
static TLorentzVector t_qq;
static TLorentzVector t_ln;
static TLorentzVector tstar_qq;
static TLorentzVector tstar_ln;
static TLorentzVector lepton;
static TLorentzVector neutrino[2]; // Two candidate solution for nu

//------------------------------------------------------------------------------ 
//   Helper functions
//------------------------------------------------------------------------------
bool fillJetPermutations( JetList& , JetList& );
void solveNeutrino( const TLorentzVector& , float , float );

float ggChannelAnalyzer::computeChiSqMass()
{
   // std::cout << "Begin mass calculation" << std::endl;

   JetPermutator p( _selectedBJetList , _selectedLJetList );
   minChiSq = 100000000.;
   if( _selectedMuonList.size() == 1 ){
      const auto& muon = _selectedMuonList[0];
      lepton = TLorentzVector( muon->px(), muon->py() , muon->pz() , muon->energy() ) ;
   } else {
      const auto& elec = _selectedElecList[0];
      lepton = TLorentzVector( elec->px() , elec->py() , elec->pz() , elec->energy() );
   }

   solveNeutrino(lepton , 0.0 , 0.0 );
   do{
      // std::cout << "Running permutation" << std::endl;
      w_qq     = p.w_h_jet1() + p.w_h_jet2() ;
      t_qq     = w_qq    + p.t_h_bjet() ;
      tstar_qq = t_qq    + p.tstar_h_jet() ;
      for( unsigned int i = 0 ; i < 2 ; ++i ){
         // cout << "Looping neutrino" << std::endl;
         w_ln     = lepton + neutrino[i] ;
         t_ln     = w_ln   + p.t_l_bjet();
         tstar_ln = t_ln   + p.tstar_l_jet();

         trial_ChiSq =  
             (( w_qq.Mag()     - W_MASS         ) * ( w_qq.Mag()     - W_MASS         )) / ( W_WIDTH     * W_WIDTH     )
            +(( t_qq.Mag()     - TOP_MASS       ) * ( t_qq.Mag()     - TOP_MASS       )) / ( TOP_WIDTH   * TOP_WIDTH   )
            +(( t_ln.Mag()     - TOP_MASS       ) * ( t_ln.Mag()     - TOP_MASS       )) / ( TOP_WIDTH   * TOP_WIDTH   )
            +(( tstar_ln.Mag() - tstar_qq.Mag() ) * ( tstar_ln.Mag() - tstar_qq.Mag() )) / ( TSTAR_WIDTH * TSTAR_WIDTH ) ;

         if( trial_ChiSq < minChiSq ){
            trial_ChiSq = minChiSq ; 
            tstarMass = (tstar_ln.Mag() + tstar_qq.Mag()) / 2.; 
         }
      }
   }while( p.permutate() );
   return tstarMass;
}


//------------------------------------------------------------------------------ 
//   Helper function implementations
//------------------------------------------------------------------------------
static float _alpha_ , _beta_    , _gamma_          ;
static float _a_     , _b_       , _c_       , _d_  ;
static float _lx_    , _ly_      , _lz_      , _lE_ ;
static float _npx_   , _npy_     , _npz_     , _nE_ ;
void solveNeutrino( const TLorentzVector& lep , float _MET_ , float _METPhi_ ) 
{
   _npx_    = _MET_ * cos( _METPhi_ )    ;
   _npy_    = _MET_ * sin( _METPhi_ )    ;

   _lx_     = lep.Px()     ;
   _ly_     = lep.Py()     ;
   _lz_     = lep.Pz()     ;
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

