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
#include "TH1F.h"

typedef std::vector<const pat::Muon*>         MuonList;
typedef std::vector<const reco::GsfElectron*> ElectronList;
typedef std::vector<const pat::Jet*>          JetList;

class BaseFilter : public MiniAODFilter {
public:
   BaseFilter( const edm::ParameterSet& );
   virtual ~BaseFilter ();

   //----- Public functions accessible by analyzers  ------------------------------
   bool isGoodPrimaryVertex( const reco::Vertex&, TH1F* );
   bool isSelectionMuon( const pat::Muon& , const reco::Vertex& , TH1F* );
   bool isSelectionElectron( const pat::Electron& , const edm::ValueMap<bool> , TH1F* );
   bool isVetoMuon( const pat::Muon& , TH1F* );
   bool isVetoElectron( const pat::Electron& , const edm::ValueMap<bool> , TH1F* );
   bool isSelectionJet( const pat::Jet& , const MuonList& , const ElectronList& , TH1F* );

protected:
   void processVertex();
   void processMuon();
   void processElectron();
   void processJet();
   virtual bool passEventSelection( TH1F* ); // Only this function is virtual for this analysis

   //----- Storage classes  -------------------------------------------------------
   reco::Vertex  _primaryVertex;
   MuonList      _selectedMuonList;
   MuonList      _vetoMuonList;
   ElectronList  _selectedElectronList;
   ElectronList  _vetoElectronList;
   JetList       _selectedJetList;

   //----- Selection efficiency tracker  ------------------------------------------
   TH1F*  _selcMuonCount;
   TH1F*  _selcElecCount;
   TH1F*  _selcJetCount;
   TH1F*  _vetoMuonCount;
   TH1F*  _vetoElecCount;
   TH1F*  _trackIsoHist;
   TH1F*  _EventCount;

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
