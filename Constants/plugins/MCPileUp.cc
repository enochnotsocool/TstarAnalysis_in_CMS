/*******************************************************************************
 *
 *  Filename    : MCPileUp.cc
 *  Description : Simple analyzer to get MC pileup distribution
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include <iostream>
#include <vector>
#include "TTree.h"
#include "TH1F.h"

static edm::Service<TFileService> fs;
static TFileDirectory  results;

class MCPileUp : public edm::EDAnalyzer {

public:
   explicit MCPileUp(const edm::ParameterSet&);
   ~MCPileUp();
   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
   virtual void beginJob() override;
   virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
   virtual void endJob() override;

   edm::Handle<std::vector<PileupSummaryInfo>> _pileUpList;
   edm::InputTag   _pileupsrc;
   //TFile*          _outputFile;
   TH1F*           _pileUpHist;
};

//------------------------------------------------------------------------------ 
//   Getting inputs
//------------------------------------------------------------------------------
MCPileUp::MCPileUp(const edm::ParameterSet& iConfig)
{
   _pileupsrc = iConfig.getParameter<edm::InputTag>( "pileupSrc" );

   results = TFileDirectory( fs->mkdir("results") );
   _pileUpHist = fs->make<TH1F>( "pileup" , "pileup" , 60 , 0 , 60  ); 
   //_outputFile = new TFile( "MCPileUp.root" , "RECREATE" );
   //_pileUpHist = new TH1F( "pileup" , "pileup" , 60 , 0 , 60 );
}

//------------------------------------------------------------------------------ 
//   Loop over events
//------------------------------------------------------------------------------
void MCPileUp::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   iEvent.getByLabel( _pileupsrc , _pileUpList );
   if( _pileUpList.isValid() ){
      _pileUpHist->Fill( _pileUpList->begin()->getTrueNumInteractions() );
   }
}

MCPileUp::~MCPileUp()
{
   // _outputFile->Write();
   //delete _outputFile;
   //delete _pileUpHist;
}


void MCPileUp::beginJob(){}
void MCPileUp::endJob() {}
void MCPileUp::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCPileUp);
