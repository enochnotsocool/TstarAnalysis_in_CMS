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
#define fillHist \
   _eventSelectionCount->Fill(i) ; ++i ;

bool gg_MuonSignal::passEventSelection( const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   unsigned int i = 0 ; 
   fillHist;
   if( !passTrigger( iEvent, iSetup ) ) { return false; }
   fillHist;
   if( _selectedMuonList.size() != 1 ){ return false; }
   fillHist ; 
   if( ! _selectedElectronList.empty() ){ return false; }
   fillHist ;
   if( ! _vetoMuonList.empty() ) { return false; }
   fillHist ; 
   if( ! _vetoElectronList.empty() ) { return false; }
   fillHist ; 
   if( _selectedJetList.size() < 6 ) { return false; }
   fillHist ; 
   if( _selectedBJetList.empty() ) { return false; }
   fillHist ;
   return true;
}


//define this as a plug-in
DEFINE_FWK_MODULE(gg_MuonSignal);
