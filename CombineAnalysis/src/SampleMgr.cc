/*******************************************************************************
 *
 *  Filename    : SampleMgr.cc
 *  Description : Implementations of files
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/SampleMgr.h"
#include "CMSSW_Utils/Utils_Functions/interface/Utils.h"
#include "TChainElement.h"
#include <iostream>
#include <stdio.h>

using namespace std;

//------------------------------------------------------------------------------ 
//   Constructor and desctructor
//------------------------------------------------------------------------------
SampleMgr::SampleMgr( const string& name, const string& latex ) :
   _name(name),_latex_name(latex)
{
   _histList = availablePlots;

   _rawEventsCount=0.;
   _eventWeightCount=0.;
   _event = new MiniEvent;
   _chain  = new TChain( "ntuplizer/TstarAnalysis" );
   _chain->SetBranchAddress( "MiniEvent" , &_event );
}

SampleMgr::SampleMgr( const SampleMgr& x ):
   _name(x._name),
   _latex_name(x._latex_name),
   _histList(x._histList),
   _cross_section(x._cross_section),
   _selection_eff(x._selection_eff),
   _sample_weight(x._sample_weight),
   _rawEventsCount(x._rawEventsCount),
   _eventWeightCount(x._eventWeightCount)
{
   _event = new MiniEvent;
   _chain = new TChain( "ntuplizer/TstarAnalysis");
   _chain->SetBranchAddress( "MiniEvent" , &_event );
}

SampleMgr::~SampleMgr()
{
   _histList.Clear();
   delete _event;
   delete _chain;
}

//------------------------------------------------------------------------------ 
//   Advanced Access member function
//------------------------------------------------------------------------------
Parameter SampleMgr::ExpectedYield( const double total_lumi ) const
{
   return total_lumi * CrossSection() * SelectionEff() * SampleWeight() 
      * (GetWeightedEventCount() / GetRawEventCount()) ; 
}

double SampleMgr::GetHistogramScale(const double total_lumi ) const
{
   double ans = ExpectedYield( total_lumi ).CentralValue();
   ans /= GetWeightedEventCount();
   return ans;
}

double SampleMgr::GetRawEventCount() const 
{
   if( _rawEventsCount == 0.0 ) {
      _rawEventsCount = _chain->GetEntries();
   }
   return _rawEventsCount;
}

double SampleMgr::GetWeightedEventCount() const 
{
   if( _eventWeightCount == 0.0 ){ 
      for( long long i = 0 ; i < _chain->GetEntries() ; ++i ){
         _chain->GetEntry(i);
         _eventWeightCount += _event->TotalEventWeight();
      }
   }
   return _eventWeightCount; 
}

//------------------------------------------------------------------------------ 
//   ROOT object interaction functions
//------------------------------------------------------------------------------
void SampleMgr::AddFile( const std::string& filename )
{
   printf("Adding file %s to sample %s\n" , filename.c_str() , _name.c_str() );
   _chain->Add( filename.c_str() );
}

void SampleMgr::SetFillColor( const Color_t& c , const float alpha = 1.0 )
{
   for( auto& hist : _histList ){
      hist.SetFillColor(c,alpha);
   }
}

void SampleMgr::SetLineColor( const Color_t& c )
{
   for( auto& hist : _histList ){
      hist.SetLineColor(c);
   }
}

//------------------------------------------------------------------------------ 
//   Private data members
//------------------------------------------------------------------------------
const string SampleMgr::MakeLatexName() const 
{
   string ans = _latex_name;
   ConvertToRegularLatex( ans );
   return ans;
}
const string SampleMgr::MakeRootTitle() const 
{
   string ans = _latex_name;
   ConvertToRootFlavorLatex( ans );
   return ans;
}


// void SampleMgr::printFileList() const
// {
//    TObjArray* fileElements = _chain->GetListOfFiles();
//    TIter next(fileElements);
//    TChainElement* chEl = 0;
//    while (( chEl=(TChainElement*)next() )) {
//       printf("      %s\n", chEl->GetTitle());
//    }
// }
