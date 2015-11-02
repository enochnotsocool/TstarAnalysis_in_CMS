/*******************************************************************************
 *
 *  Filename    : SampleMgr.cc
 *  Description : Implementations of files
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "SampleMgr.h"
#include <iostream>
#include <stdio.h>

//------------------------------------------------------------------------------ 
//   Helper variables
//------------------------------------------------------------------------------
static std::string  plotname;
static std::string  xtitle;
static std::string  ytitle;
static unsigned int binCount;
static float xmax;
static float xmin;

//------------------------------------------------------------------------------ 
//   Constructor and desctructor
//------------------------------------------------------------------------------
SampleMgr::SampleMgr( const std::string& name ) 
{
   _name   = name ;
   _chain  = new TChain( "ntuplizer/TstarAnalysis" );
   _cross_section = 1. ;
   _selection_eff = 0. ; 

   for( const auto& pair : availiableList  ){
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
      if( _name == "Data" ){
         Hist( plotname )->SetMarkerStyle( 21 );
      }
   }
}

SampleMgr::~SampleMgr()
{
   for( auto hist_pair : _histMap ){
      delete hist_pair.second;
   }
}

//------------------------------------------------------------------------------ 
//   Basic access function
//------------------------------------------------------------------------------
const std::string& SampleMgr::name() const{
   return _name ; }

void SampleMgr::addFile( const std::string& filename )
{
   printf("Adding file %s to %s\n" , filename.c_str() , _name.c_str() );
   _chain->Add( filename.c_str() );
}



TH1F* SampleMgr::Hist( const std::string& histname )
{
   return _histMap[histname];
}

void SampleMgr::setFillColor( const Color_t c  )
{
   for( auto histpair : _histMap ){
      histpair.second->SetFillColor( c  );
   }
   _fillColor = c;
}

void SampleMgr::setLineColor( const Color_t c )
{
   for( auto histpair : _histMap ){
      histpair.second->SetLineColor( c  );
   }
   _lineColor = c ;
}

void SampleMgr::Print( float totalLumi ) const 
{
   std::cout << "--------------------------------------------" << std::endl;
   std::cout << "   Name:         " << _name << std::endl;
   std::cout << "   Files:        " << "MyFile.root" << std::endl;
   std::cout << "   Event Count:  " << getRawEventCount() << std::endl;
   if( _name != "Data" ){
      std::cout << "   XSection:   " << _cross_section << std::endl;
      std::cout << "   Efficiency: " << _selection_eff << std::endl;
      std::cout << "   Exp. Yield: " << getExpectedYield(totalLumi) << std::endl;
   }
   std::cout << "--------------------------------------------\n" << std::endl;
}


float SampleMgr::crossSection() const { return _cross_section;}
void  SampleMgr::setCrossSection( const float x ){ _cross_section = x ; }
float SampleMgr::selectionEff() const { return _selection_eff;}
void  SampleMgr::setSelectionEff( const float x ){ _selection_eff = x ; }


//------------------------------------------------------------------------------ 
//   Private member functions
//------------------------------------------------------------------------------
void SampleMgr::addHist( const std::string& histname , int nbin , float xmin , float xmax )
{
   TH1F* temp = new TH1F( (_name+histname).c_str() , (_name+histname).c_str() , nbin , xmin , xmax );
   printf( "New Histogram %s at %p\n" , histname.c_str() , temp );
   _histMap[ histname ] = temp ;
}
