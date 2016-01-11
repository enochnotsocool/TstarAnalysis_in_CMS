/*******************************************************************************
 *
 *  Filename    : SampleMgr.cc
 *  Description : Implementations of files
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/SampleMgr.h"
#include "TChainElement.h"
#include <iostream>
#include <stdio.h>

//------------------------------------------------------------------------------ 
//   Helper variables
//------------------------------------------------------------------------------
static PlotName   plotname;
static std::string  xtitle;
static std::string  ytitle;
static unsigned int binCount;
static float xmax;
static float xmin;

//------------------------------------------------------------------------------ 
//   Constructor and desctructor
//------------------------------------------------------------------------------
SampleMgr::SampleMgr( const SampleName& name ) 
{
   _name   = name ;
   _chain  = new TChain( "ntuplizer/TstarAnalysis" );
   setSampleWeight( 1. );
   setCrossSection( 1. );
   setSelectionEff( 0. );

   _histMap.clear();
   for( const auto& pair : availiablePlots  ){
      plotname = pair.first;
      binCount = pair.second.BinCount();
      xmax     = pair.second.XMax();
      xmin     = pair.second.XMin();
      xtitle   = pair.second.Xtitle();
      ytitle   = pair.second.Ytitle();
      addHist( plotname , binCount , xmin , xmax );
      Hist( plotname )->SetLineColor( kBlack );
      Hist( plotname )->GetXaxis()->SetTitle( xtitle.c_str() );
      Hist( plotname )->GetYaxis()->SetTitle( ytitle.c_str() );
      if( _name == Data ){
         Hist( plotname )->SetMarkerStyle( 21 );
      }
   }
   _rawEventsCount=0.;
   _eventWeightCount=0.;
   _event = new MiniEvent;
   _chisq = new ChiSquareResult;
   _hitfit = new HitFitResult;
   _chain->SetBranchAddress( "MiniEvent" , &_event );
   _chain->SetBranchAddress( "ChiSquareResult" , &_chisq );
   _chain->SetBranchAddress( "HitFitResult" , &_hitfit );
}

SampleMgr::~SampleMgr()
{
   for( auto hist_pair : _histMap ){
      delete hist_pair.second;
   }
}

//------------------------------------------------------------------------------ 
//   Basic access functions
//------------------------------------------------------------------------------
const SampleName& SampleMgr::name() const{ return _name ; }
float SampleMgr::crossSection() const { return _cross_section.CentralValue();}
void  SampleMgr::setCrossSection( const Parameter& x ){ _cross_section = x ; }
float SampleMgr::selectionEff() const { return _selection_eff.CentralValue();}
void  SampleMgr::setSelectionEff( const Parameter& x ){ _selection_eff = x ; }
float SampleMgr::sampleWeight() const { return _sample_weight.CentralValue();}
void  SampleMgr::setSampleWeight( const float x ){ _sample_weight.SetCentralValue(x) ; }

void SampleMgr::Print( float totalLumi ) const 
{
   std::cout << "--------------------------------------------" << std::endl;
   std::cout << "   Name:           " << Stringify(_name) << std::endl;
   std::cout << "   Files:          " << std::endl;
   printFileList();
   std::cout << "   Event Count:    " << getRawEventCount() << std::endl;
   if( _name != Data ){
      std::cout << "   Weighted Count: " << getTotalWeightedCount() << std::endl;
      std::cout << "      Event Based Average: "  << getAverageEventWeight() << std::endl;
      std::cout << "      Sample Weight:       "  << sampleWeight() << std::endl;
      std::cout << "   XSection:    " << _cross_section << std::endl;
      std::cout << "   Efficiency:  " << _selection_eff << std::endl;
      std::cout << "   Exp. Yield:  " << getExpectedYield(totalLumi) << std::endl;
   }
   std::cout << "--------------------------------------------\n" << std::endl;
}

void SampleMgr::PrintTable( const float totalLumi ) const 
{
   if( _name != Data ){
//      printf( "%s & $%d$ & $%lf^{%lf}_{%lf}$  &  $%lf^{%lf}_{%lf} $    &     & \\\\n"
   }
}

//------------------------------------------------------------------------------ 
//   ROOT object interaction functions
//------------------------------------------------------------------------------
void SampleMgr::addFile( const std::string& filename )
{
   printf("Adding file %s to sample %s\n" , filename.c_str() , Stringify(_name).c_str() );
   _chain->Add( filename.c_str() );
}

TH1F* SampleMgr::Hist( const PlotName& histname ) 
{ 
   return _histMap.at(histname); 
}
const TH1F* SampleMgr::Hist( const PlotName& name ) const
{
   return _histMap.at(name);
}

void SampleMgr::setColor( const Color_t& c )
{
   setFillColor( c );
   setLineColor( c );
}

void SampleMgr::setFillColor( const Color_t& c , const float alpha )
{
   for( auto histpair : _histMap ){
      histpair.second->SetFillColorAlpha( c , alpha );
   }
   _fillColor = c;
}

void SampleMgr::setLineColor( const Color_t& c )
{
   for( auto histpair : _histMap ){
      histpair.second->SetLineColor( c  );
   }
   _lineColor = c ;
}

//------------------------------------------------------------------------------ 
//   Root object interaction helper private functions
//------------------------------------------------------------------------------
void SampleMgr::addHist( const PlotName& histname , int nbin , float xmin , float xmax )
{
   std::string temp = Stringify(_name) + Stringify(histname);
   TH1F* newhist = new TH1F( temp.c_str() , temp.c_str() , nbin , xmin , xmax );
   _histMap[ histname ] = newhist ;
}

void SampleMgr::printFileList() const
{
   TObjArray* fileElements = _chain->GetListOfFiles();
   TIter next(fileElements);
   TChainElement* chEl = 0;
   while (( chEl=(TChainElement*)next() )) {
      printf("      %s\n", chEl->GetTitle());
   }
}
