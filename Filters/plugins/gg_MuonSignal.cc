/*******************************************************************************
 *
 *  Filename    : gg_MuonSignal.cc
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
   _acceptTriggers.push_back( "HLT_IsoMu27_v1" ); // MC_reminiAOD
   _acceptTriggers.push_back( "HLT_IsoMu27_v2" ); // Data
   _acceptTriggers.push_back( "HLT_IsoMu27_v3" ); // Data
}

gg_MuonSignal::~gg_MuonSignal()
{
   
}

//------------------------------------------------------------------------------ 
//   Muon Signal criteria
//------------------------------------------------------------------------------

bool gg_MuonSignal::passEventSelection( const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   int i = 0 ; 
   FillHistAtBin( _eventSelectionCount , i ); 
   if( !passTrigger( iEvent, iSetup ) ) { return false; }
   FillHistAtBin( _eventSelectionCount , i ); 
   if( _selectedMuonList.size() != 1 ){ return false; }
   FillHistAtBin( _eventSelectionCount , i ); 
   if( ! _selectedElectronList.empty() ){ return false; }
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
DEFINE_FWK_MODULE(gg_MuonSignal);
