/*******************************************************************************
 *
 *  Filename    : ChannelMgr_MakeLatex.cc
 *  Description : Printing summary into latex format
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

//------------------------------------------------------------------------------ 
//   Making Channel Summary
//------------------------------------------------------------------------------
void ChannelMgr::MakeLatexSummary() const
{
   cout << "Make Latex file!" << endl;
   SummaryHeader();
   SummarySection( _MCSampleTable["Signal"] );
   for( const auto& list : _MCSampleTable ){
      if( list.Name() != "Signal" ){
         SummarySection( list ); }
   }
   SummaryEnd();
}

const string ChannelMgr::SummaryFileName() const 
{
   return  "./data/tables/" + _name +  "_summary.tex";
}

void ChannelMgr::SummaryHeader() const 
{
   FILE* latex = fopen( SummaryFileName().c_str() ,"w" );
   fprintf( latex, "\\begin{tabular}{|c|ccc|}\n" );
   fprintf( latex, "\\hline\n" );
   fprintf( latex, "%-15s & %-15s & %-15s & %-15s \\\\\n" , 
         "Source" , 
         "Cross Section($pb^{-1}$)" ,
         "Selection Efficiency(\\\%)" , 
         "Expected Yield");
   fprintf( latex, "\\hline\n" );
   
   fclose( latex );
}

void ChannelMgr::SummarySection( const SampleList& list ) const 
{
   FILE* latex = fopen( SummaryFileName().c_str() ,"a" );
   Parameter eff_sel;
   string name;
   string crx;
   string eff;
   string yield;
   
   for( const auto& sample : list ){
      eff_sel = sample.CrossSection()*sample.SampleWeight();
      name = sample.Name();
      crx  = sample.CrossSection().MakeLatex();
      eff  = eff_sel.MakeLatex();
      yield = sample.ExpectedYield( _totalLumi ).MakeLatex();

      fprintf( latex , "%-50s & %30s & %30s & %30s \\\\\n",
            name.c_str(),
            crx.c_str(),
            eff.c_str(),
            yield.c_str() );
   }

   fclose( latex );
}

void ChannelMgr::SummaryEnd() const
{
   FILE* latex = fopen( SummaryFileName().c_str() ,"a" );
   Parameter totalYield(0,0,0);

   // Calculating total yield;
   for( const auto& list : _MCSampleTable ){
      if( list.Name() == "Signal" ) { continue; }
      for( const auto& bg : list ){
         totalYield += bg.ExpectedYield( _totalLumi );
      }
   }
   
   // Printing to File
   fprintf( latex, "total background & & & %s \\\\\n", totalYield.MakeLatex().c_str() );
   fprintf( latex, "\\hline\n" );
   fprintf( latex, "Data & & & %lf \\\\\n", _dataSample.GetRawEventCount() );
   fprintf( latex, "\\hline\n" );
   fprintf( latex, "\\end{tabular}\n" );

   fclose( latex );
}
