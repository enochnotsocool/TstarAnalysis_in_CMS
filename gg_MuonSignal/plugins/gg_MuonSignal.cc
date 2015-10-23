/*******************************************************************************
 *
 *  Filename    : gg_MuonSignal.cc
 *  Description : gg Channel Muon signal
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#include "TstarAnalysis/BaseFilter/interface/BaseFilter.h"

class gg_MuonSignal : public BaseFilter {
public:
   explicit gg_MuonSignal(const edm::ParameterSet&);
   ~gg_MuonSignal();
protected:
   bool passEventSelection( TH1F* );
};

gg_MuonSignal::gg_MuonSignal(const edm::ParameterSet& iConfig):
   BaseFilter(iConfig){}

gg_MuonSignal::~gg_MuonSignal(){}


bool gg_MuonSignal::passEventSelection( TH1F* )
{
   return true;
}

DEFINE_FWK_MODULE(gg_MuonSignal);
