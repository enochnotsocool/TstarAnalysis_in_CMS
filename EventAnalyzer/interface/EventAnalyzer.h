/*******************************************************************************
 *
 *  Filename    : EventAnalyzer.h
 *  Description : The interaction framework with the CMSSW framework
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : All events are stored in the _masterList, 
 *                Events will only include cleaned particles. 
 *
*******************************************************************************/
#ifndef __EVENTANALYZER_H__
#define __EVENTANALYZER_H__

//------------------------------------------------------------------------------ 
//   EDAnalyzer requirements
//------------------------------------------------------------------------------
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//------------------------------------------------------------------------------ 
//   Self written helper classes
//------------------------------------------------------------------------------
#include "TstarAnalysis/EventAnalyzer/interface/MiniEvent.h"
#include "TstarAnalysis/EventAnalyzer/interface/Region.h"

class EventAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
   explicit EventAnalyzer( const edm::ParameterSet& );
   ~EventAnalyzer();
   static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );

private:
   virtual void beginJob() override;
   virtual void analyze( const edm::Event&, const edm::EventSetup& ) override;
   virtual void endJob() override;

   //----- Private data members  -----------------------------------------------
   std::vector<MiniEvent> _masterEventList;
   std::vector<Region*>   _regionList;
};

#endif // __EVENTANALYZER_H__



