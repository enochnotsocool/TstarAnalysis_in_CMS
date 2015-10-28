/*******************************************************************************
 *
 *  Filename    : SampleInfo.cc
 *  Description : Implementations of files
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "SampleInfo.h"
#include <iostream>
#include <stdio.h>

//------------------------------------------------------------------------------ 
//   Constructor and desctructor
//------------------------------------------------------------------------------
SampleInfo::SampleInfo( const std::string& name , const std::string& ntuple ) 
{
   _name   = name ;
   _chain  = new TChain( ntuple.c_str() );
   _cross_section = 1. ;
   _selection_eff = 1. ; 

   for( int i = 0 ; i < PLOT_NAME_COUNT ; ++i ){
      addHist( plotname[i] , binCount[i] , 0 , histMax[i] );
   }
}

SampleInfo::~SampleInfo()
{
   for( auto hist_pair : _histMap ){
      delete hist_pair.second;
   }
}

//------------------------------------------------------------------------------ 
//   Basic access function
//------------------------------------------------------------------------------
void SampleInfo::addFile( const std::string& filename )
{
   printf("Adding file %s to %s\n" , filename.c_str() , _name.c_str() );
   _chain->Add( filename.c_str() );
}



TH1F* SampleInfo::Hist( const std::string& histname )
{
   return _histMap[histname];
}

void SampleInfo::setFillColor( const Color_t c  )
{
   for( auto histpair : _histMap ){
      histpair.second->SetFillColor( c  );
   }
   _fillColor = c;
}

void SampleInfo::setLineColor( const Color_t c )
{
   for( auto histpair : _histMap ){
      histpair.second->SetLineColor( c  );
   }
   _lineColor = c ;
}

void SampleInfo::HistPlot( const std::string& name , const std::string& style )
{
   _histMap[name]->Draw( style.c_str() );
}

void SampleInfo::Print() const 
{
   std::cout << "--------------------------------------------" << std::endl;
   std::cout << "   Name: " << _name << std::endl;
   std::cout << "   Type: " << "Data" << std::endl;
   std::cout << "   Files:" << "MyFile.root" << std::endl;
   std::cout << "   Color:" << _fillColor << std::endl;
   std::cout << "   LineColor: " << _lineColor << std::endl;
   std::cout << "--------------------------------------------\n" << std::endl;
}


float SampleInfo::crossSection() const { return _cross_section;}
void  SampleInfo::setCrossSection( const float x ){ _cross_section = x ; }
float SampleInfo::selectionEff() const { return _selection_eff;}
void  SampleInfo::setSelectionEff( const float x ){ _selection_eff = x ; }


//------------------------------------------------------------------------------ 
//   Private member functions
//------------------------------------------------------------------------------
void SampleInfo::addHist( const std::string& histname , int nbin , float xmin , float xmax )
{
   TH1F* temp = new TH1F( (_name+histname).c_str() , (_name+histname).c_str() , nbin , xmin , xmax );
   _histMap[ histname ] = temp ;
}
