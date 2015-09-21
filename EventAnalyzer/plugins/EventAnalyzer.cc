#include "TstarAnalysis/EventAnalyzer/interface/EventAnalyzer.h"

EventAnalyzer::EventAnalyzer( const edm::ParameterSet& iConfig )
{
   usesResource( "TFileService" );


}


EventAnalyzer::~EventAnalyzer()
{
   //----- Clearing pointer variables  ----------------------------------------------------------------
   for( size_t i = 0 ; i < _regionList.size() ; ++i ){
      delete _regionList[i];
   }
}

// ------------ method called for each event  ------------
void
EventAnalyzer::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
   // Constructing a clean event, for construction process seed the code in MiniEvent.cc
   MiniEvent cleanEvent( iEvent ) ; 
   
   // Looping over defined regions
   for( auto& region : _regionList ) {
      if( region->isRegionEvent( cleanEvent ) ){
         region->pushback( &cleanEvent ) ;
         region->processEvent( cleanEvent ) ;
      }
   } 
}


// ------------ method called once each job just before starting event loop  ------------
void EventAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void EventAnalyzer::endJob()
{
   for( auto* region: _regionList ){
      region->process();
   }
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
EventAnalyzer::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
   //The following says we do not know what parameters are allowed so do no validation
   // Please change this to state exactly what you do use, even if it is no parameters
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault( desc );
}

//define this as a plug-in
DEFINE_FWK_MODULE( EventAnalyzer );
