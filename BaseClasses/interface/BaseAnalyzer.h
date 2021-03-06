/*******************************************************************************
 *
 *  Filename    : BaseAnalyzer.h
 *  Description : Base Analyzer class for TstarAnalysis
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __BASEANALYZER_H__
#define __BASEANALYZER_H__

#include "TstarAnalysis/BaseClasses/interface/MiniAODAnalyzer.h"
#include "TstarAnalysis/BaseClasses/interface/TypeDefs.h"
#include "TstarAnalysis/BaseClasses/interface/ObjectSelection.h"

#include "TstarAnalysis/RootFormat/interface/MiniEvent.h"

#include "TTree.h"


class BaseAnalyzer : public MiniAODAnalyzer {
public:
   BaseAnalyzer( const edm::ParameterSet& );
   virtual ~BaseAnalyzer ();

protected:
   void processVertex(const edm::Event& , const edm::EventSetup&);
   void processMuon(const edm::Event& , const edm::EventSetup& );
   void processElectron(const edm::Event& , const edm::EventSetup& );
   void processJet(const edm::Event& , const edm::EventSetup& );
   void processEvent(const edm::Event& , const edm::EventSetup& );

   void addEventVariables(const edm::Event& );
   void addMuon();
   void addJet();
   void addElectron();
   //Adding analysis specific variables
   virtual void addCustomVariables(const edm::Event&);
   
   //----- Storage classes  -------------------------------------------------------
   reco::Vertex  _primaryVertex;
   MuonList      _selectedMuonList;
   ElectronList  _selectedElectronList;
   JetList       _selectedLJetList;
   JetList       _selectedBJetList;

   TTree*  _tree;
   MiniEvent*  _event;

   unsigned _debug;

private:
   void beginJob();
   void endJob();

   //----- Additional variables  --------------------------------------------------
   edm::EDGetTokenT<edm::ValueMap<bool>>  eleLooseIdMapToken_   ;
   edm::EDGetTokenT<edm::ValueMap<bool>>  eleMediumIdMapToken_  ;
   edm::Handle<edm::ValueMap<bool>>  loose_id_decisions  ;
   edm::Handle<edm::ValueMap<bool>>  medium_id_decisions ;
   ObjectSelection  _objSel;
};

#endif // __BASEANALYZER_H__
