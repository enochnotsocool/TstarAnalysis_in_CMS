/*******************************************************************************
 *
 *  Filename    : JetPermutator.cc
 *  Description : Implementation of JetPermutator class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/ggChannelAnalyzer/interface/JetPermutator.h"
#include <algorithm>
#include <iostream>
//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
JetPermutator::JetPermutator(  const JetList& inputBJetList, const JetList& inputLJetList )
{
   //----- Getting inputs  --------------------------------------------------------
   for( const auto& jet : inputBJetList ){
      _rawbjetList.push_back( jet ) ;
   }
   std::sort( _rawbjetList.begin() , _rawbjetList.end() );
   for( const auto& jet : inputLJetList ){
      _rawljetList.push_back( jet ) ;
   }
   std::sort( _rawljetList.begin() , _rawljetList.end() );

   if( inputBJetList.size() > 2 ) {
      std::cout << "Warning! input b jet list (size:" << inputBJetList.size() 
         << ")is larger than required (2)! Permutation algorithm may misbehave!!" << std::endl ; 
   }
}
JetPermutator::~JetPermutator(){}

//------------------------------------------------------------------------------ 
//   Main Functions
//------------------------------------------------------------------------------

bool JetPermutator::permutate()
{
   static TLorentzVector temp;
   _returnVector.clear();
   for( const auto& jet : _rawbjetList ) {
      temp.SetPxPyPzE( jet->px() , jet->py() , jet->pz() , jet->energy() );
      _returnVector.push_back( temp );
   }
   for( const auto& jet : _rawljetList ){
      if( _returnVector.size() == 6 ) break; 
      temp.SetPxPyPzE( jet->px() , jet->py() , jet->pz() , jet->energy() );
      _returnVector.push_back( temp );
   }
   bool bretVal = next_permutation( _rawbjetList.begin() , _rawbjetList.end() ) ;
   bool lretVal = next_permutation( _rawljetList.begin() , _rawljetList.end() ) ;
   return ( bretVal || lretVal );
}