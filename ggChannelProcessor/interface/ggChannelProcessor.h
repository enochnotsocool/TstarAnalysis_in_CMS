/*******************************************************************************
 *
 *  Filename    : ggChannelProcessor.h
 *  Description : ED Analyzer for single sample analysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  In this package, we attempt to pull all the information we need for a
 *  cross sample analysis into a flat root format.
 *
*******************************************************************************/
#ifndef __GGCHANNELANALYZER_H__
#define __GGCHANNELANALYZER_H__

//----- ED Analyzer requirements  ----------------------------------------------
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//----- Formats  ---------------------------------------------------------------
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "TstarAnalysis/Selection/interface/Selection.h"
#include "TstarAnalysis/RootFormat/interface/MiniJetBranches.h"
#include "TstarAnalysis/RootFormat/interface/MiniElectronBranches.h"
#include "TstarAnalysis/RootFormat/interface/MiniMuonBranches.h"
#include "TstarAnalysis/RootFormat/interface/MiniEventBranches.h"

#include "TTree.h"

class ggChannelProcessor : public edm::EDAnalyzer {
public:
   explicit ggChannelProcessor( const edm::ParameterSet& );
   ~ggChannelProcessor();
   static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );

private:
   virtual void beginJob() override;
   virtual void analyze( const edm::Event&, const edm::EventSetup& ) override;
   virtual void endJob() override;

   //----- Helper functions  ------------------------------------------------------
   void  GetSelectionObjects();
   void  FillTree(const edm::Event& );
   void  addEventInfo( const edm::Event& );
   void  addJet( const pat::Jet* );
   void  addMuon( const pat::Muon* );
   void  addElec( const reco::GsfElectron* );
   bool  isMuonEvent();
   bool  isElectronEvent();

   //----- Specific analysis variables  -------------------------------------------
   float computeChiSqMass();
   void  permutatedJets();

   //----- Physical objects storage  ----------------------------------------------
   reco::Vertex                          _primaryVertex    ;
   std::vector<const pat::Muon*>         _selectedMuonList ;
   std::vector<const reco::GsfElectron*> _selectedElecList ;
   std::vector<const pat::Jet*>          _selectedBJetList  ;
   std::vector<const pat::Jet*>          _selectedLJetList  ;

   //----- Output Root format handling  -------------------------------------------
   TTree* _tree;
   MiniEventBranches    _eventBranches;
   MiniMuonBranches     _muonBranches;
   MiniElectronBranches _elecBranches;
   MiniJetBranches      _jetBranches;

   //----- MiniAOD interaction varaibles  -----------------------------------------
   edm::InputTag _muonsrc ;
   edm::InputTag _elecsrc ;
   edm::InputTag _jetsrc  ;
   edm::InputTag _metsrc  ;
   edm::InputTag _vertexsrc ;
   edm::InputTag _convsrc ;
   edm::InputTag _rhosrc ;
   edm::InputTag _beamspotsrc ;
   edm::InputTag _pileupsrc;

   edm::Handle<double>                         _rawRho; 
   edm::Handle<reco::BeamSpot>                 _rawBeamSpot;
   edm::Handle<reco::VertexCollection>         _rawVertexList;
   edm::Handle<edm::View<reco::GsfElectron>>   _rawElectronList;
   edm::Handle<edm::View<pat::Muon>>           _rawMuonList;
   edm::Handle<edm::View<pat::Jet>>            _rawJetList;
   edm::Handle<reco::ConversionCollection>     _rawConversionList;
   edm::Handle<std::vector<pat::MET>>          _rawMETList;
   edm::Handle<std::vector<PileupSummaryInfo>> _rawPileupList; 
};

#endif // __GGCHANNELANALYZER_H__
