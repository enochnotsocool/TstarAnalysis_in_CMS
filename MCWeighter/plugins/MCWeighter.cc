/*******************************************************************************
 *
 *  Filename    : MCWeighter.cc
 *  Description : Class for determining sample wide MC weights
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "MiniAODAnalysis/BaseAnalyzer/interface/MiniAODAnalyzer.h"
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
   float  _weightedEventCount;
};

MCWeighter::MCWeighter(const edm::ParameterSet& iConfig) :
   MiniAODAnalyzer(iConfig)
{}

MCWeighter::~MCWeighter(){}


// ------------ method called once each job just before starting event loop  ------------
void MCWeighter::beginJob()
{
   _totalEventCount = 0;
   _weightedEventCount = 0 ;
}

// ------------ method called once each job just after ending the event loop  ------------
void MCWeighter::endJob() 
{
   cout << "[MCWEIGHTER] Total Events:" << _totalEventCount << endl;
   cout << "[MCWEIGHTER] Total Weight:" << _weightedEventCount << endl;
}

void MCWeighter::processEvent(const edm::Event&,const edm::EventSetup&)
{
   _totalEventCount++;
   if( _genHandle.isValid() ){
      _weightedEventCount += _genHandle->weight();}
}

DEFINE_FWK_MODULE(MCWeighter);
