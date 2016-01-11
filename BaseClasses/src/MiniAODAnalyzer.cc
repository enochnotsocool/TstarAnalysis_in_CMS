/*******************************************************************************
 *
 *  Filename    : MiniAODAnalyzer.cc
 *  Description : Basic function for miniAOD analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/BaseClasses/interface/MiniAODAnalyzer.h"

//------------------------------------------------------------------------------ 
//   Constructor and Destructor
//------------------------------------------------------------------------------
MiniAODAnalyzer::MiniAODAnalyzer(const edm::ParameterSet& iConfig)
{
   GET_MINIAOD_LABELS;
}

MiniAODAnalyzer::~MiniAODAnalyzer(){}


//------------------------------------------------------------------------------ 
//   Main code segment
//------------------------------------------------------------------------------
void MiniAODAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   GET_MINIAOD_OBJS;

   processVertex(iEvent,iSetup);
   processMuon(iEvent,iSetup);
   processElectron(iEvent,iSetup);
   processJet(iEvent,iSetup);

   processEvent(iEvent,iSetup);
}

//----- Virtual functions to be overloaded  ------------------------------------
void MiniAODAnalyzer::processVertex(const edm::Event&,const edm::EventSetup&){}
void MiniAODAnalyzer::processMuon(const edm::Event&,const edm::EventSetup&){}
void MiniAODAnalyzer::processElectron(const edm::Event&,const edm::EventSetup&){}
void MiniAODAnalyzer::processJet(const edm::Event&,const edm::EventSetup&){}
void MiniAODAnalyzer::processEvent(const edm::Event&,const edm::EventSetup&){}

// ------------ method called once each job just before starting event loop  ------------
void MiniAODAnalyzer::beginJob(){}

// ------------ method called once each job just after ending the event loop  ------------
void MiniAODAnalyzer::endJob() {}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MiniAODAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MiniAODAnalyzer);
