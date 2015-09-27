/*******************************************************************************
 *
 *  Filename    : ggChannelFilter.h
 *  Description : Class declaration for ggChannel Event Filter
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *               Class implementation will be split into two files
 *               One in the ggChannelFilter.cc for the plugin interaction
 *               and the ggChannelFilter_Selection.cc for the object 
 *               cleaning and event selection parts
 *
*******************************************************************************/
#ifndef __GGCHANNELFILTER_H__
#define __GGCHANNELFILTER_H__

//----- ED Plugin requirements  --------------------------------------------------------------------
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

//----- MiniAOD interaction classes  ---------------------------------------------------------------
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"

class ggChannelFilter : public edm::stream::EDFilter<> {
public:
   explicit ggChannelFilter( const edm::ParameterSet& );
   ~ggChannelFilter();

   static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );
private:
   virtual void beginStream( edm::StreamID ) override;
   virtual bool filter( edm::Event&, const edm::EventSetup& ) override;
   virtual void endStream() override;

   //----- Helper functions  --------------------------------------------------------------------------
   bool getPrimaryVertex(const edm::Event&, const edm::EventSetup&);
   bool passMuonCleaning(const edm::Event&, const edm::EventSetup&);
   bool passElectronCleaning(const edm::Event&, const edm::EventSetup&);
   bool passJetCleaning(const edm::Event&, const edm::EventSetup&);
   bool passEventSelection(const edm::Event&, const edm::EventSetup&);

   bool isGoodPV( const reco::Vertex* ) const ;
   bool isLooseMuon( const pat::Muon* ) const ;
   bool isTightMuon( const pat::Muon* ) const ;
   bool isLooseElec( const pat::Electron* ) const ;
   bool isTightElec( const pat::Electron* ) const ;
   bool isLooseJet( const pat::Jet* ) const ;

   //----- MiniAOD interaction members  ---------------------------------------------------------------
   edm::InputTag _muonsrc ;
   edm::InputTag _elecsrc ;
   edm::InputTag _jetsrc  ;
   edm::InputTag _metsrc  ;
   edm::InputTag _vertexsrc ;

   //----- Temporary storage members  -----------------------------------------------------------------
   reco::Vertex  _primaryVertex ; 
   std::vector<const pat::Muon*>      _looseMuonList;
   std::vector<const pat::Muon*>      _tightMuonList;
   std::vector<const pat::Electron*>  _looseElecList;
   std::vector<const pat::Electron*>  _tightElecList;
   std::vector<const pat::Jet*>       _looseJetList;

   size_t totalEvent;
   size_t passedEvent;
};

#endif // __GGCHANNELFILTER_H__
