/*******************************************************************************
 *
 *  Filename    : filterAnalyzer.h
 *  Description : Analyzing various performance of analyzer
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  Plot various historgrams of selection efficiency
 *
*******************************************************************************/
#ifndef __FILTERANALYZER_H__
#define __FILTERANALYZER_H__

//----- EDM Plugin requirements  -----------------------------------------------
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//----- Required Headers  ------------------------------------------------------
#include "TH1F.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

class filterAnalyzer : public edm::EDAnalyzer {
public:
   explicit filterAnalyzer( const edm::ParameterSet& );
   ~filterAnalyzer();

   static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );


private:
   virtual void beginJob() override;
   virtual void analyze( const edm::Event&, const edm::EventSetup& ) override;
   virtual void endJob() override;

   //----- Helper functions  --------------------------------------------------------------------------
   bool getPrimaryVertex(const edm::Event&, const edm::EventSetup&);
   bool passMuonCleaning(const edm::Event&, const edm::EventSetup&);
   bool passElectronCleaning(const edm::Event&, const edm::EventSetup&);
   bool passJetCleaning(const edm::Event&, const edm::EventSetup&);
   bool passEventSelection(const edm::Event&, const edm::EventSetup&);

   //----- MiniAOD interaction members  ---------------------------------------------------------------
   edm::InputTag _muonsrc ;
   edm::InputTag _elecsrc ;
   edm::InputTag _jetsrc  ;
   edm::InputTag _metsrc  ;
   edm::InputTag _vertexsrc ;
   edm::InputTag _convsrc ;
   edm::InputTag _rhosrc ;
   edm::InputTag _beamspotsrc ;

   edm::Handle<double>                       _rawRho; 
   edm::Handle<reco::BeamSpot>               _rawBeamSpot;
   edm::Handle<reco::VertexCollection>       _rawVertexList;
   edm::Handle<edm::View<reco::GsfElectron>> _rawElectronList;
   edm::Handle<edm::View<pat::Muon>>         _rawMuonList;
   edm::Handle<edm::View<pat::Jet>>          _rawJetList;
   edm::Handle<reco::ConversionCollection>   _rawConversionList; 

   //----- Temporary storage members  -----------------------------------------------------------------
   reco::Vertex                           _primaryVertex ; 
   std::vector<const pat::Muon*>          _vetoMuonList;
   std::vector<const pat::Muon*>          _selcMuonList;
   std::vector<const reco::GsfElectron*>  _vetoElecList;
   std::vector<const reco::GsfElectron*>  _selcElecList;
   std::vector<const pat::Jet*>           _ljetList;
   std::vector<const pat::Jet*>           _bjetList;
   
   //----- Counting historgrams  -------------------------------------------------
   TH1F* _eventCount;
   TH1F* _selcMuonCount;
   TH1F* _selcElecCount;
   TH1F* _selcJetCount;
};


#endif // __FILTERANALYZER_H__




