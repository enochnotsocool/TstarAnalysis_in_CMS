/*******************************************************************************
 *  *
 *   *  Filename    : PlotDef.h
 *    *  Description : Class for managing plot constants
 *     *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *      *
 *      *******************************************************************************/
#ifndef __PLOTDEF_H__
#define __PLOTDEF_H__

#include <string>
#include <map>

enum PlotName {
   JetCount = 0,
   JetPt = 1,
   JetEta = 2,
   LeptonPt = 10,
   LeptonEta = 11,
   MET  = 20,
   VertexCount = 21,
   
   ChiSquareTstarMass = 50,
   ChiSquareTMass = 51, 

   HitFitTstarMass = 60,
   HitFitTMass = 61 ,

   PLOTNAME_END
};

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

typedef std::pair<const PlotName, PlotDef> PlotPair;
typedef std::map<const PlotName, PlotDef>  PlotList;

extern PlotList availiablePlots;
extern bool     initPlotList();
extern std::string Stringify( const PlotName );
extern PlotName PlotNameFromString( const std::string& );
extern bool CheckPlotName( const PlotName );

#endif // __PLOTDEF_H__
