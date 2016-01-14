/*******************************************************************************
 *
 *  Filename    : HistMgr.cc
 *  Description : Implementation of plotDef class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/HistMgr.h"

#include "CMSSW_Utils/Utils_Functions/interface/Utils.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

//------------------------------------------------------------------------------ 
//   Delcaring Global variables
//------------------------------------------------------------------------------
HistList   availablePlots;

//------------------------------------------------------------------------------ 
//   Static Dummy variables 
//------------------------------------------------------------------------------
static HistMgr  _dummy_hist_("DUMMY");
static unsigned FontType = 43;
static unsigned FontSize = 16;

//------------------------------------------------------------------------------ 
//   HistMgr Member funtions
//------------------------------------------------------------------------------
HistMgr::HistMgr( const string& name ):
   _name(name),
   _hist(NULL)
{
}

HistMgr::HistMgr( const HistMgr& x ):
   _name(x._name),
   _hist(NULL)
{
   *this = x ;
}


HistMgr::~HistMgr()
{
   if(_hist != NULL ) { delete _hist; }
}

void HistMgr::MakeHist( const string& inputname = "" )
{
   if( _hist != NULL ) { delete _hist; _hist = NULL; }
   const string fulltitle = Title() + ";" + Xtitle()+ "(" + XUnits() + ");" + Ytitle() ;
   string unique_name;
   if( inputname == "" ){ unique_name = _name+RandomString(6); }
   else unique_name = inputname ; 
   _hist = new TH1F( unique_name.c_str(), fulltitle.c_str() , BinCount() , XMin() , XMax() );
   
   // Default styling 
   _hist->SetFillStyle(1001);
   _hist->SetStats(0);
   _hist->SetLineColor(kBlack);
   _hist->GetXaxis()->SetTitleFont(FontType);
   _hist->GetXaxis()->SetLabelFont(FontType);
   _hist->GetXaxis()->SetTitleSize(FontSize);
   _hist->GetXaxis()->SetLabelSize(FontSize);
   _hist->GetYaxis()->SetTitleFont(FontType);
   _hist->GetYaxis()->SetLabelFont(FontType);
   _hist->GetYaxis()->SetTitleSize(FontSize);
   _hist->GetYaxis()->SetLabelSize(FontSize);

}

const string HistMgr::MakeHistTitle() const 
{
   if( XUnits() != "" ){
      return Title() + ";" + Xtitle()+ "(" + XUnits() + ");" + Ytitle() ; 
   } else {
      return Title() + ";" + Xtitle() + " ;" + Ytitle() ; 
   }
}

const std::string HistMgr::MakeYtitle() const
{
   static char  buffer[1024];
   static double binWidth;
   binWidth = (_xmax-_xmin)/(double)_binCount ;
   if( fabs(binWidth-1.0)<0.0001){
      if( _xunits == "" ){
         sprintf( buffer , "Yield" );
      } else {
         sprintf( buffer , "Yield/%s" , _xunits.c_str() );
      }
   } else {
      if( _xunits == "" ){
         sprintf( buffer , "Yield/%0.2f" , binWidth );
      } else {
         sprintf( buffer , "Yield / (%0.2f %s)" , 
               binWidth , _xunits.c_str() );
      }
   }
   return  buffer;
}

const std::string HistMgr::MakeLatexName()  const 
{
   string ans = _title;
   ConvertToRegularLatex(ans);
   return ans;
}

const std::string HistMgr::MakeRootTitle() const 
{
   string ans = _title;
   ConvertToRootFlavorLatex(ans);
   return ans;
}

HistMgr& HistMgr::operator=( const HistMgr& x )
{
   _binCount = x._binCount ;
   _xmax  = x._xmax ;
   _xmin  = x._xmin ;
   _title = x._title ;
   _xtitle = x._xtitle ;
   _xunits = x._xunits ;
   if( _hist != NULL ){
      delete _hist;
   }
   if( x._hist != NULL ){
      _hist = (TH1F*)x._hist->Clone();
   } else {
      _hist = NULL;
   }

   return *this;
}

//------------------------------------------------------------------------------ 
//   HistList Member Functions
//------------------------------------------------------------------------------
HistList::HistList()
{
}

HistList::HistList( const HistList& x ):
   _list(x._list)
{
}

HistList::~HistList()
{
}

HistMgr& HistList::operator[]( const string& x )
{
   for( auto& hist : _list ){
      if( hist.Name() == x ) { return hist; }
   }
   cerr << "Plot (" << x << ") Not found! Returning Dummy" << endl;
   return _dummy_hist_;
}
const HistMgr& HistList::operator[]( const string& x ) const
{
   for( const auto& hist : _list ){
      if( hist.Name() == x ) { return hist; }
   }
   cerr << "Plot (" << x << ") Not found! Returning Dummy" << endl;
   return _dummy_hist_;
}

bool HistList::InitFromFile( const std::string& cfgfile )
{
   unsigned line_num = 0;
   ifstream file( cfgfile );
   string line;
   vector<string> tokens;
   
   cout << "Initializing plots from file (" << cfgfile << ") ..." << endl; 
   while( getline(file,line) ){
      cout << "\rReading line " << ++line_num << flush;
      if(!BreakLineToWords(line,tokens,"|")){ continue; }
      for( auto& token : tokens ){
         StripTrailingSpace(token); }

      for( const auto& token : tokens ){
         cout << token << ";" ;
      } cout << endl;
      if( tokens.size() != 7 ){
         continue;
      } 
      const string& name      = tokens[0];
      const string& latexname = tokens[1];
      const string& xtitle    = tokens[2];
      const string& xunits    = tokens[3];
      unsigned bincount       = StrToInt( tokens[4] );
      double   xmin           = StrToFloat( tokens[5] );
      double   xmax           = StrToFloat( tokens[6] );

      _list.push_back( HistMgr( name ) );
      _list.back().SetTitle( latexname );
      _list.back().SetXtitle( xtitle );
      _list.back().SetXunits( xunits );
      _list.back().SetBinCount( bincount );
      _list.back().SetXMin( xmin );
      _list.back().SetXMax( xmax );
      _list.back().MakeHist(); 
   }
   _dummy_hist_.MakeHist();
   return true;
}

bool HistList::HasHistogram( const std::string& name ) const
{
   for( const auto& hist : _list ){
      if( hist.Name() == name ){ return true; }
   }
   return false;
}

void HistList::Print() const 
{
   cout << "\n-----------------------------------------------" << endl;
   for( const auto& hist : _list ){
      cout << hist.Name() << " " << hist.Title() << endl;
   }
   cout << "\n-----------------------------------------------" << endl;
}



