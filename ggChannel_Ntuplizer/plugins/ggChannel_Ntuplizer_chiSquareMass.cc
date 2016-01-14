/*******************************************************************************
 *
 *  Filename    : ggChannel_Ntuplizer_chiSqMass.cc
 *  Description : Computing chi square mass
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/ggChannel_Ntuplizer/interface/ggChannel_Ntuplizer.h"
#include <iostream>

void ggChannel_Ntuplizer::RunChiSquare()
{
   _chisqSolver.SetMET( *(_metList->begin()) );

   if( _selectedMuonList.size() == 1 ){
      _chisqSolver.SetLepton( _selectedMuonList[0] );
   } else {
      _chisqSolver.SetLepton( _selectedElectronList[0] );
   }

   _chisqSolver.SetBJetList( _selectedBJetList );
   _chisqSolver.SetLJetList( _selectedLJetList );

   _chisqSolver.RunPermutations();

   _event->GetChiSquare() = _chisqSolver.BestResult();

}
