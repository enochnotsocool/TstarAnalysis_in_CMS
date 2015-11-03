/*******************************************************************************
 *
 *  Filename    : PlotDef.h
 *  Description : Class for managing plot constants
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef __PLOTDEF_H__
#define __PLOTDEF_H__

#include <string>
#include <map>

class PlotDef;
typedef std::pair<const std::string, PlotDef> PlotPair;
typedef std::map<const std::string, PlotDef>  PlotList;

class PlotDef {
public: 
   PlotDef();
   virtual ~PlotDef ();

   void setXMax( const float );
   void setXMin( const float );
   void setBinCount( const unsigned int );
   void setTitle( const std::string& );
   void setXtitle( const std::string& );
   void makeYtitle( const std::string& );
   void setYtitle( const std::string& );

   unsigned int BinCount() const ;
   float XMax() const ;
   float XMin() const ;
   const std::string& Title() const ;
   const std::string& Xtitle() const ;
   const std::string& Ytitle() const ;

private:
   unsigned int _binCount;
   float _xmax ;
   float _xmin ;
   std::string  _title;
   std::string  _xtitle;
   std::string  _ytitle;
};

extern PlotList availiableList;
extern bool     initPlotList();

#endif // __PLOTDEF_H__

