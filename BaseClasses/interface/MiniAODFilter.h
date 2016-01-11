/*******************************************************************************
 *
 *  Filename    : MiniAODFilter.h
 *  Description : Base class for MiniAOD analysis 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef __MINIAODFILTER_H__
#define __MINIAODFILTER_H__

//----- EDFilter Requirements  -------------------------------------------------
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//----- MiniAOD interaction objects definition  --------------------------------
#include "TstarAnalysis/BaseClasses/interface/MiniAODContainer.h"
//----- File output  -----------------------------------------------------------
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1F.h"

//------------------------------------------------------------------------------ 
//   Class definition
//------------------------------------------------------------------------------
class MiniAODFilter : public edm::EDFilter {
public:
   explicit MiniAODFilter(const edm::ParameterSet&);
   ~MiniAODFilter();
   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

protected:
   //----- Pure virtual functions for derived class  ------------------------------
   virtual void processVertex( const edm::Event& , const edm::EventSetup& );
   virtual void processMuon(const edm::Event& , const edm::EventSetup& );
   virtual void processElectron(const edm::Event& , const edm::EventSetup& );
   virtual void processJet(const edm::Event& , const edm::EventSetup& );
   virtual bool passEventSelection(const edm::Event& , const edm::EventSetup& );
   virtual bool passTrigger( const edm::Event& , const edm::EventSetup& );

   /******************************************************************************/
   MINIAOD_OBJS; // See Containers
   /******************************************************************************/ 
   TH1F*  _eventSelectionCount;
private:
   virtual void beginJob() override;
   virtual bool filter(edm::Event&, const edm::EventSetup&) override;
   virtual void endJob() override;
};


#endif // __MINIAODFILTER_H__
