/*******************************************************************************
 *
 *  Filename    : SampleMgr.h
 *  Description : Define class of sample ntuple file class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __SAMPLEINFO_H__
#define __SAMPLEINFO_H__

#include <vector>
#include <string>
#include <map>
#include "TChain.h"
#include "TH1F.h"
#include "PlotDef.h"

typedef std::map<const std::string,TH1F*>  HistMap; 

class SampleMgr {
public:
   SampleMgr( const std::string& );
   virtual ~SampleMgr ();

   const std::string& name() const;
   void  Print(float) const;

   void  addFile( const std::string& );
   float crossSection() const ;
   void  setCrossSection( const float ) ;
   float selectionEff() const ;
   void  setSelectionEff( const float ) ;

   TH1F* Hist( const std::string& );
   void  HistPlot( const std::string& , const std::string& );
   float getRawEventCount() const;
   float getWeightedEventCount() const;
   float getExpectedYield( float ) const ;
   void  makeBasicPlots();

   const std::string& plotStyle() const ;
   void  setFillColor( const Color_t& , const float=1.0 );
   void  setLineColor( const Color_t& );

private:
   std::string  _name;
   TChain*      _chain;
   Color_t      _fillColor;
   Color_t      _lineColor;
   HistMap      _histMap;
   float        _cross_section;
   float        _selection_eff;
   
   void addHist( const std::string& , int ,  float , float );
   void printFileList() const;
};


#endif // __SAMPLEINFO_H__
