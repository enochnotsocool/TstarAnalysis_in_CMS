/*******************************************************************************
 *
 *  Filename    : gg_MuonSignal.cc
 *  Description : ggChannel Muon Signal regions definition
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/BaseClasses/interface/BaseFilter.h"
#include <iostream>

//------------------------------------------------------------------------------ 
//   Class declaration
//------------------------------------------------------------------------------
class gg_MuonSignal : public BaseFilter {
public:
   explicit gg_MuonSignal(const edm::ParameterSet&);
   ~gg_MuonSignal();

   virtual bool passEventSelection( const edm::Event&, const edm::EventSetup&  );

protected:
};

gg_MuonSignal::gg_MuonSignal( const edm::ParameterSet& iConfig ):
   BaseFilter( iConfig )
{
   std::cout << "MAKING NEW" << std::endl;

}

gg_MuonSignal::~gg_MuonSignal()
{
   
}

//------------------------------------------------------------------------------ 
//   Muon Signal criteria
//------------------------------------------------------------------------------
bool gg_MuonSignal::passEventSelection( const edm::Event& , const edm::EventSetup& )
{
   _eventSelectionCount->Fill(0);
   if( _selectedMuonList.size() != 1 ){ return false; }
   _eventSelectionCount->Fill(1);
   if( ! _selectedElectronList.empty() ){ return false; }
   _eventSelectionCount->Fill(2);
   if( ! _vetoMuonList.empty() ) { return false; }
   _eventSelectionCount->Fill(3);
   if( ! _vetoElectronList.empty() ) { return false; }
   _eventSelectionCount->Fill(4);
   if( _selectedJetList.size() < 6 ) { return false; }
   _eventSelectionCount->Fill(5);
   if( _selectedBJetList.empty() ) { return false; }
   _eventSelectionCount->Fill(6);
   if( _selectedBJetList[0]->pt() < 50. ){ return false; }
   _eventSelectionCount->Fill(7);
   if( _selectedJetList[0]->pt() < 50. ) { return false; }
   _eventSelectionCount->Fill(8);
   return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(gg_MuonSignal);
