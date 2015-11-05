/*******************************************************************************
 *
 *  Filename    : gg_ElectronSignal.cc
 *  Description : ggChannel Muon Signal regions definition
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/BaseClasses/interface/BaseFilter.h"
#include "FWCore/Common/interface/TriggerNames.h"
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
   _acceptTriggers.push_back( "HLT_Ele32_eta2p1_WPTight_Gsf_v2" );
}

gg_ElectronSignal::~gg_ElectronSignal()
{
   
}

//------------------------------------------------------------------------------ 
//   Electron Signal criteria
//------------------------------------------------------------------------------
#define fillHist \
   _eventSelectionCount->Fill(i) ; ++i ;

bool gg_ElectronSignal::passEventSelection( const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   unsigned int i = 0 ;
   fillHist;
   if( !passTrigger(iEvent,iSetup) ){ return false; }
   fillHist;
   if( _selectedElectronList.size() != 1 ){ return false; }
   fillHist;
   if( ! _selectedMuonList.empty() ){ return false; }
   fillHist;
   if( ! _vetoMuonList.empty() ) { return false; }
   fillHist;
   if( ! _vetoElectronList.empty() ) { return false; }
   fillHist;
   if( _selectedJetList.size() < 6 ) { return false; }
   fillHist;
   if( _selectedBJetList.empty() ) { return false; }
   fillHist;
   return true;
}


//define this as a plug-in
DEFINE_FWK_MODULE(gg_ElectronSignal);
