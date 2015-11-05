/*******************************************************************************
 *
 *  Filename    : BaseFilter.h
 *  Description : Base filter for all filters 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Since object selection will mostly be the same, we are not going 
 *  are going to define the object selection functions here
 *
*******************************************************************************/
#ifndef __BASEFILTER_H__
#define __BASEFILTER_H__

#include "MiniAODAnalysis/BaseFilter/interface/MiniAODFilter.h"
#include "TstarAnalysis/BaseClasses/interface/TypeDefs.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "TH1F.h"

class BaseFilter : public MiniAODFilter {
public:
   BaseFilter( const edm::ParameterSet& );
   virtual ~BaseFilter ();

protected:
   void processVertex(const edm::Event& , const edm::EventSetup&);
   void processMuon(const edm::Event& , const edm::EventSetup& );
   void processElectron(const edm::Event& , const edm::EventSetup& );
   void processJet(const edm::Event& , const edm::EventSetup& );
   bool passTrigger(const edm::Event&, const edm::EventSetup& );
   // Only these function is virtual for this analysis
   virtual bool passEventSelection(const edm::Event& , const edm::EventSetup& ); 
   
   //----- Storage classes  -------------------------------------------------------
   reco::Vertex  _primaryVertex;
   MuonList      _selectedMuonList;
   MuonList      _vetoMuonList;
   ElectronList  _selectedElectronList;
   ElectronList  _vetoElectronList;
   JetList       _selectedJetList;
   JetList       _selectedBJetList;
   std::vector<std::string>  _acceptTriggers;

   //----- Selection efficiency tracker  ------------------------------------------
   TH1F*  _selcMuonCount;
   TH1F*  _selcElecCount;
   TH1F*  _selcJetCount;
   TH1F*  _vetoMuonCount;
   TH1F*  _vetoElecCount;

private:
   void beginJob();
   void endJob();

   //----- Additional variables  --------------------------------------------------
   edm::EDGetTokenT<edm::ValueMap<bool>>  eleLooseIdMapToken_   ;
   edm::EDGetTokenT<edm::ValueMap<bool>>  eleMediumIdMapToken_  ;
   edm::Handle<edm::ValueMap<bool>>  loose_id_decisions  ;
   edm::Handle<edm::ValueMap<bool>>  medium_id_decisions ;
};

#endif // __BASEFILTER_H__
