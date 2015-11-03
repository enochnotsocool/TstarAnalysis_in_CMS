/*******************************************************************************
 *
 *  Filename    : gg_ElectronSignal.cc
 *  Description : ggChannel Muon Signal regions definition
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/BaseClasses/interface/BaseFilter.h"
#include <iostream>

//------------------------------------------------------------------------------ 
//   Class declaration
//------------------------------------------------------------------------------
class gg_ElectronSignal : public BaseFilter {
public:
   explicit gg_ElectronSignal(const edm::ParameterSet&);
   ~gg_ElectronSignal();

   virtual bool passEventSelection( const edm::Event&, const edm::EventSetup&  );

protected:
};

gg_ElectronSignal::gg_ElectronSignal( const edm::ParameterSet& iConfig ):
   BaseFilter( iConfig )
{

}

gg_ElectronSignal::~gg_ElectronSignal()
{
   
}

//------------------------------------------------------------------------------ 
//   Electron Signal criteria
//------------------------------------------------------------------------------
bool gg_ElectronSignal::passEventSelection( const edm::Event& , const edm::EventSetup& )
{
   _eventSelectionCount->Fill(0);
   if( _selectedElectronList.size() != 1 ){ return false; }
   _eventSelectionCount->Fill(1);
   if( ! _selectedMuonList.empty() ){ return false; }
   _eventSelectionCount->Fill(2);
   if( ! _vetoMuonList.empty() ) { return false; }
   _eventSelectionCount->Fill(3);
   if( ! _vetoElectronList.empty() ) { return false; }
   _eventSelectionCount->Fill(4);
   if( _selectedJetList.size() < 6 ) { return false; }
   _eventSelectionCount->Fill(5);
   if( _selectedBJetList.empty() ) { return false; }
   _eventSelectionCount->Fill(6);
   return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(gg_ElectronSignal);
