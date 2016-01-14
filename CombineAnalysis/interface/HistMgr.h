/*******************************************************************************
 *  *
 *   *  Filename    : HistMgr.h
 *    *  Description : Class for managing plot constants
 *     *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *      *
 *      *******************************************************************************/
#ifndef __PLOTDEF_H__
#define __PLOTDEF_H__

#include <string>
#include <vector>
#include "TH1F.h"

class HistMgr;
class HistList;

extern HistList availablePlots;
extern void PrintPlotList();

class HistMgr {
public:
   HistMgr( const std::string& );
   HistMgr( const HistMgr& );
   virtual ~HistMgr ();
   void MakeHist( const std::string& );

   TH1F* operator()() { return _hist; }
   const TH1F* operator()() const { return _hist; }
   const std::string& Name() const { return _name; }
   const std::string  LatexName() const { return MakeLatexName(); }
   const std::string  Title() const { return MakeRootTitle(); }
   const std::string& Xtitle() const { return _xtitle; }
   const std::string& XUnits() const { return _xunits; }
   const std::string  Ytitle() const { return MakeYtitle(); }
   unsigned  BinCount() const { return _binCount; }
   double    XMax() const { return _xmax; }
   double    XMin() const { return _xmin; }
   
   void SetTitle(  const std::string& x ) { _title = x; }
   void SetXtitle( const std::string& x ) { _xtitle = x; }
   void SetXunits( const std::string& x ) { _xunits = x; }
   void SetBinCount( const unsigned x ) { _binCount = x; }
   void SetXMax( const double x ) { _xmax = x; }
   void SetXMin( const double x ) { _xmin = x; }
   void SetLineColor( const Color_t x ) { _hist->SetLineColor(x); }
   void SetFillColor( const Color_t x , const double a = 1.0 ){
      _hist->SetFillColorAlpha(x,a); }

   const std::string MakeHistTitle() const; 
   HistMgr& operator=( const HistMgr& );


private:
   const std::string  _name;
   unsigned  _binCount;
   double    _xmax ;
   double    _xmin ;
   std::string  _title;
   std::string  _xtitle;
   std::string  _xunits;
   TH1F*  _hist;
  
   const std::string MakeLatexName() const ;
   const std::string MakeRootTitle() const;
   const std::string MakeYtitle() const ;
};

class HistList
{
public:
   HistList();
   HistList( const HistList& );
   virtual ~HistList ();

   //----- STL like access functions  --------------------------------------------- 
   typedef std::vector<HistMgr>::iterator       iterator;
   typedef std::vector<HistMgr>::const_iterator const_iterator;
   iterator begin() { return _list.begin(); }
   iterator end()   { return _list.end(); }
   const_iterator begin() const { return _list.begin(); }
   const_iterator end()   const { return _list.end(); }
   void AddHist( const HistMgr& x ) { _list.push_back(x); }
   void Clear() { _list.clear(); }

   HistMgr&       operator[]( const std::string& );
   const HistMgr& operator[]( const std::string& ) const ;
   bool HasHistogram( const std::string& ) const ;

   bool InitFromFile( const std::string& );
   void Print() const;


private:
   std::vector<HistMgr>   _list; 
};

#endif // __PLOTDEF_H__
