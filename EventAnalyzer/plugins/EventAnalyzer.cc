/***************************************************************************************************
 *
 *  Filename    : EventAnalyzer.cc
 *  Description : Generic functions for EDAnlysier
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : This files includes the virtual functions and explicit functions required 
 *                for the standard EDAnalyzer. For details of function implementation
 *                read the varius plugins/ _*.cc files
 *
***************************************************************************************************/
#include "TstarAnalysis/EventAnalyzer/interface/EventAnalyzer.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
   
EventAnalyzer::EventAnalyzer( const edm::ParameterSet& iConfig )
{
   edm::Service<TFileService> fs;
   jetSelection = fs->make<TH1F>( "JetSelection" , "JetSelection" , 5 , 0 , 5 ) ;
   for( int i = 0 ; i < 1000 ; ++i ){
      jetSelection->Fill(0.5);
   }
}


EventAnalyzer::~EventAnalyzer()
{
   //----- Clearing pointer variables  ------------------------------------------
   for( size_t i = 0 ; i < _regionList.size() ; ++i ){
      delete _regionList[i];
   }
   delete jetSelection ; 
}

// ------------ method called for each event  ------------
void
EventAnalyzer::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
   // Constructing a clean event, for construction process seed the code in MiniEvent.cc
   getCleanParticles( iEvent , iSetup ) ;

   MiniEvent* cleanEvent = new MiniEvent;
   makeEvent( cleanEvent , iEvent, iSetup );
   
   for( auto& region : _regionList ) {
      if( region->isRegionEvent( cleanEvent )  ){
         region->pushback( cleanEvent ) ;
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


void EventAnalyzer::makeEvent( MiniEvent* ,const edm::Event& , const edm::EventSetup& )  const 
{
}

//define this as a plug-in
DEFINE_FWK_MODULE( EventAnalyzer );
