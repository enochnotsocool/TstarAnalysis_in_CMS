/*******************************************************************************
 *
 *  Filename    : MCWeighter.cc
 *  Description : Class for determining sample wide MC weights
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "MiniAODAnalysis/BaseAnalyzer/interface/MiniAODAnalyzer.h"
#include "TH1F.h"
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

   TH1F*  _weightHist;
   size_t _totalEventCount;
   size_t _negativeEventCount;
   size_t _positiveEventCount;
   float  _weightSum;
};

MCWeighter::MCWeighter(const edm::ParameterSet& iConfig) :
   MiniAODAnalyzer(iConfig)
{
   _weightHist = fs->make<TH1F>( "WeightHist" , "WeightHist" , 100, -100 , 100 );
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
}

void MCWeighter::processEvent(const edm::Event&,const edm::EventSetup&)
{
   float weight;
   _totalEventCount++;
   if( _genHandle.isValid() ){
      weight = _genHandle->weight();
      _weightSum  += weight ;
      if( weight > 0 ) {
         ++_positiveEventCount;
      } else {
         ++_negativeEventCount;
      }
      _weightHist->Fill(weight);
   }
}

DEFINE_FWK_MODULE(MCWeighter);
