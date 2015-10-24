/*******************************************************************************
 *
 *  Filename    : gg_MuonSignal.cc
 *  Description : ggChannel Muon Signal regions definition
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/BaseClasses/interface/BaseFilter.h"
#include <iostream>

//------------------------------------------------------------------------------ 
//   Class declaration
//------------------------------------------------------------------------------
class gg_MuonSignal : public BaseFilter {
public:
   explicit gg_MuonSignal(const edm::ParameterSet&);
   ~gg_MuonSignal();

   virtual bool passEventSelection( const edm::Event&, const edm::EventSetup&  );

protected:
};

gg_MuonSignal::gg_MuonSignal( const edm::ParameterSet& iConfig ):
   BaseFilter( iConfig )
{
   std::cout << "MAKING NEW" << std::endl;

}

gg_MuonSignal::~gg_MuonSignal()
{
   
}

//------------------------------------------------------------------------------ 
//   Muon Signal criteria
//------------------------------------------------------------------------------
bool gg_MuonSignal::passEventSelection( const edm::Event& , const edm::EventSetup& )
{
   std::cout << "Testing 0 ...." << std::endl; 
   if( _selectedMuonList.size() != 1 ){ return false; }
   std::cout << "Testing 1 ...." << std::endl; 
   if( ! _selectedElectronList.empty() ){ return false; }
   std::cout << "Testing 2 ...." << std::endl; 
   if( ! _vetoMuonList.empty() ) { return false; }
   std::cout << "Testing 3 ...." << std::endl; 
   if( ! _vetoElectronList.empty() ) { return false; }
   std::cout << "Testing 4 ...." << std::endl; 
   if( _selectedJetList.size() < 6 ) { return false; }
   std::cout << "Testing 5 ...." << std::endl; 
   if( _selectedBJetList.empty() ) { return false; }
   std::cout << "Testing 6 " << _selectedBJetList.size() << "...." << std::endl; 
   if( _selectedBJetList[0]->pt() < 50. ){ return false; }
   std::cout << "Testing 7 ...." << std::endl; 
   if( _selectedJetList[0]->pt() < 50. ) { return false; }
   std::cout << "Done!" << std::endl;
   return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(gg_MuonSignal);
