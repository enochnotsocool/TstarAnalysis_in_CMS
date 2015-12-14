/*******************************************************************************
 *
 *  Filename    : gg_ElectronSignal.cc
 *  Description : ggChannel Muon Signal regions definition
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/BaseClasses/interface/BaseFilter.h"
#include "TstarAnalysis/BaseClasses/interface/Utils.h"
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
   _acceptTriggers.push_back( "HLT Ele27 eta2p1 WPLoose Gsf_v1" );
   _acceptTriggers.push_back( "HLT Ele27 eta2p1 WPLoose Gsf_v2" );
   _acceptTriggers.push_back( "HLT Ele27 eta2p1 WPLoose Gsf_v3" );
   _acceptTriggers.push_back( "HLT Ele27 eta2p1 WPLoose Gsf_v4" );
}

gg_ElectronSignal::~gg_ElectronSignal()
{
   
}

//------------------------------------------------------------------------------ 
//   Electron Signal criteria
//------------------------------------------------------------------------------

bool gg_ElectronSignal::passEventSelection( const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   int i = 0 ;
   FillHistAtBin( _eventSelectionCount , i );
   if( !passTrigger(iEvent,iSetup) ){ return false; }
   FillHistAtBin( _eventSelectionCount , i );
   if( _selectedElectronList.size() != 1 ){ return false; }
   FillHistAtBin( _eventSelectionCount , i );
   if( ! _selectedMuonList.empty() ){ return false; }
   FillHistAtBin( _eventSelectionCount , i );
   if( ! _vetoMuonList.empty() ) { return false; }
   FillHistAtBin( _eventSelectionCount , i );
   if( ! _vetoElectronList.empty() ) { return false; }
   FillHistAtBin( _eventSelectionCount , i );
   if( _selectedJetList.size() < 6 ) { return false; }
   FillHistAtBin( _eventSelectionCount , i );
   if( _selectedBJetList.empty() ) { return false; }
   FillHistAtBin( _eventSelectionCount , i );
   return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(gg_ElectronSignal);
