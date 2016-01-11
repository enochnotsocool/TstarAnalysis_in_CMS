/*******************************************************************************
 *
 *  Filename    : MiniAODFilter.cc
 *  Description : Implementation for non-pure virtual functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TstarAnalysis/BaseClasses/interface/MiniAODFilter.h"

//------------------------------------------------------------------------------ 
//   Constructor and destructor
//------------------------------------------------------------------------------
MiniAODFilter::MiniAODFilter(const edm::ParameterSet& iConfig)
{
   GET_MINIAOD_LABELS; //See definition in MiniAODAnalysis/MiniAODContainer

   _eventSelectionCount = fs->make<TH1F>( "EventSelection" , "EventSelection" , 10 , 0 , 10 );
}

MiniAODFilter::~MiniAODFilter(){}

//------------------------------------------------------------------------------ 
//   Dummy filter process
//------------------------------------------------------------------------------
bool MiniAODFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   GET_MINIAOD_OBJS; //See definition in    
   processVertex(iEvent,iSetup);
   processMuon(iEvent,iSetup);
   processElectron(iEvent,iSetup);
   processJet(iEvent,iSetup);
   return passEventSelection(iEvent,iSetup);
}

//------------------------------------------------------------------------------ 
//   Dummy functions, remember to overload
//------------------------------------------------------------------------------
void MiniAODFilter::processVertex(const edm::Event& , const edm::EventSetup& ) {}
void MiniAODFilter::processMuon(const edm::Event& , const edm::EventSetup& ) {}
void MiniAODFilter::processElectron(const edm::Event& , const edm::EventSetup& ) {}
void MiniAODFilter::processJet(const edm::Event& , const edm::EventSetup& ){}
bool MiniAODFilter::passEventSelection(const edm::Event& , const edm::EventSetup& ){ return true; }
bool MiniAODFilter::passTrigger(const edm::Event&, const edm::EventSetup&){return true;}

void  MiniAODFilter::beginJob(){}
void MiniAODFilter::endJob() {}
void MiniAODFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(MiniAODFilter);
