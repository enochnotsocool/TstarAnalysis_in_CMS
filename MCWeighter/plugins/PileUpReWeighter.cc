/*******************************************************************************
 *
 *  Filename    : PileUpReWeighter.cc
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

class PileUpReWeighter : public edm::EDAnalyzer {

public:
   explicit PileUpReWeighter(const edm::ParameterSet&);
   ~PileUpReWeighter();
   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
   virtual void beginJob() override;
   virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
   virtual void endJob() override;

   edm::Handle<std::vector<PileupSummaryInfo>> _pileUpList;
   edm::InputTag   _pileupsrc;
   int             _binCount;
   //TFile*          _outputFile;
   TH1F*           _pileUpHist;
};

//------------------------------------------------------------------------------ 
//   Getting inputs
//------------------------------------------------------------------------------
PileUpReWeighter::PileUpReWeighter(const edm::ParameterSet& iConfig)
{
   _pileupsrc = iConfig.getParameter<edm::InputTag>( "pileupSrc" );
   _binCount  = iConfig.getParameter<int>( "binCount" );

   results = TFileDirectory( fs->mkdir("results") );
   _pileUpHist = fs->make<TH1F>( "pileup" , "pileup" , _binCount , 0 , _binCount  ); 
   //_outputFile = new TFile( "PileUpReWeighter.root" , "RECREATE" );
   //_pileUpHist = new TH1F( "pileup" , "pileup" , 60 , 0 , 60 );
}

//------------------------------------------------------------------------------ 
//   Loop over events
//------------------------------------------------------------------------------
void PileUpReWeighter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   iEvent.getByLabel( _pileupsrc , _pileUpList );
   if( _pileUpList.isValid() ){
      _pileUpHist->Fill( _pileUpList->begin()->getTrueNumInteractions() );
   }
}

PileUpReWeighter::~PileUpReWeighter()
{
   // _outputFile->Write();
   //delete _outputFile;
   //delete _pileUpHist;
}


void PileUpReWeighter::beginJob(){}
void PileUpReWeighter::endJob() {}
void PileUpReWeighter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PileUpReWeighter);
