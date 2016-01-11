/*******************************************************************************
 *
 *  Filename    : MCWeighter.cc
 *  Description : Class for determining sample wide MC weights
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/BaseClasses/interface/MiniAODAnalyzer.h"
#include "TH1F.h"
#include <stdio.h>
#include <iostream>

using namespace std;

class MCWeighter : public MiniAODAnalyzer {
public:
   explicit MCWeighter(const edm::ParameterSet&);
   ~MCWeighter();

protected:
   void processEvent(const edm::Event&,const edm::EventSetup&);

private:
   void beginJob();
   void endJob();

   size_t _totalEventCount;
   size_t _negativeEventCount;
   size_t _positiveEventCount;
   double  _weightSum;
};

MCWeighter::MCWeighter(const edm::ParameterSet& iConfig) :
   MiniAODAnalyzer(iConfig)
{
}

MCWeighter::~MCWeighter(){}


// ------------ method called once each job just before starting event loop  ------------
void MCWeighter::beginJob()
{
   _totalEventCount = 0;
   _positiveEventCount = 0 ;
   _negativeEventCount = 0 ;
   _weightSum = 0 ;
}

// ------------ method called once each job just after ending the event loop  ------------
void MCWeighter::endJob() 
{
   cout << "[MCWEIGHTER] Total-Events:    " << _totalEventCount << endl;
   cout << "[MCWEIGHTER] Positive-Events: " << _positiveEventCount << endl;
   cout << "[MCWEIGHTER] Negative-Events: " << _negativeEventCount << endl;
   cout << "[MCWEIGHTER] Total-Weight:    " << _weightSum << endl;
   cout << "[MCWEIGHTER] Average Weight:  " << _weightSum/_totalEventCount << endl;
}

void MCWeighter::processEvent(const edm::Event& iEvent,const edm::EventSetup&)
{
   float weight;
   _totalEventCount++;
   if( _lheHandle.isValid() ){
      weight = _lheHandle->weights().at(0).wgt;
      if( weight > 0 ) {
         ++_positiveEventCount;
      } else {
         ++_negativeEventCount;
         weight *= -1.;
      }
      weight /= _lheHandle->hepeup().XWGTUP;
      _weightSum  += weight ;
   }
}

DEFINE_FWK_MODULE(MCWeighter);
