/*******************************************************************************
 *
 *  Filename    : MiniAODAnalyzer.h
 *  Description : Basic analyzer for miniAOD format
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef __BASEANALYSER_H__
#define __BASEANALYSER_H__

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

//------------------------------------------------------------------------------ 
//   Class definition
//------------------------------------------------------------------------------
class MiniAODAnalyzer : public edm::EDAnalyzer {
public:
   explicit MiniAODAnalyzer(const edm::ParameterSet&);
   ~MiniAODAnalyzer();

   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

protected:
   //----- Pure virtual functions for derived class  ------------------------------
   virtual void processVertex( const edm::Event& , const edm::EventSetup& );
   virtual void processMuon(const edm::Event& , const edm::EventSetup& );
   virtual void processElectron(const edm::Event& , const edm::EventSetup& );
   virtual void processJet(const edm::Event& , const edm::EventSetup& );
   virtual void processEvent( const edm::Event&, const edm::EventSetup& );

   /******************************************************************************/
   MINIAOD_OBJS;
   /******************************************************************************/

private:
   virtual void beginJob() override;
   virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
   virtual void endJob() override;

};


#endif // __BASEANALYSER_H__
