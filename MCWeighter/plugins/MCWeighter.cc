/*******************************************************************************
 *
 *  Filename    : MCWeighter.cc
 *  Description : Class for determining sample wide MC weights
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "MiniAODAnalysis/BaseAnalyzer/interface/MiniAODAnalyzer.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
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

   TH1F*  _weightHist;
   TH1F*  _systematicWeights;
   size_t _totalEventCount;
   size_t _negativeEventCount;
   size_t _positiveEventCount;
   double  _weightSum;
};

MCWeighter::MCWeighter(const edm::ParameterSet& iConfig) :
   MiniAODAnalyzer(iConfig)
{
   _weightHist = fs->make<TH1F>( "WeightHist" , "WeightHist" , 100, -100 , 100 );
   _systematicWeights = fs->make<TH1F>( "SysWeight" , "SysWeight" , 1000 , -2 , 2 );
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
      weight = _lheHandle->weights().at(29).wgt;
      if( weight > 0 ) {
         ++_positiveEventCount;
      } else {
         ++_negativeEventCount;
         weight *= -1.;
      }
      weight /= _lheHandle->hepeup().XWGTUP;
      _weightSum  += weight ;
   }
   if( _genHandle.isValid() ){
      cout << "PDF ID1 " << _genHandle->pdf()->id.first << endl ; 
      cout << "PDF ID2 " << _genHandle->pdf()->id.second << endl; 
      cout << "PDF x1 " << _genHandle->pdf()->x.first << endl ; 
      cout << "PDF x2 " << _genHandle->pdf()->x.second << endl ; 
      cout << "PDF v1 " << _genHandle->pdf()->xPDF.first << endl ; 
      cout << "PDF v2 " << _genHandle->pdf()->xPDF.first << endl ;
      cout << "PDFSCALE" << _genHandle->pdf()->scalePDF << endl << endl;
   }
   edm::Handle<LHERunInfoProduct> run; 
   typedef std::vector<LHERunInfoProduct::Header>::const_iterator headers_const_iterator;

   iEvent.getByLabel( edm::InputTag("externalLHEProducer") , run );
   LHERunInfoProduct myLHERunInfoProduct = *(run.product());

   for (headers_const_iterator iter=myLHERunInfoProduct.headers_begin(); iter!=myLHERunInfoProduct.headers_end(); iter++){
      std::cout << iter->tag() << std::endl;
      std::vector<std::string> lines = iter->lines();
      for (unsigned int iLine = 0; iLine<lines.size(); iLine++) {
         std::cout << lines.at(iLine);
      }
   }

}

DEFINE_FWK_MODULE(MCWeighter);
