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

   //----- Basic info functions  --------------------------------------------------
   const std::string& name() const;
   float crossSection() const ;
   void  setCrossSection( const float ) ;
   float selectionEff() const ;
   void  setSelectionEff( const float ) ;
   float sampleWeight() const ;
   void  setSampleWeight( const float );
   void  Print(float) const;

   //----- ROOT object interaction  -----------------------------------------------
   TH1F* Hist( const std::string& );
   void  addFile( const std::string& );
   void  setLineColor( const Color_t& );
   void  setFillColor( const Color_t& , const float=1.0 );

   //----- Computation functions  -------------------------------------------------
   float getRawEventCount() const;
   float getEventWeightedCount() const ;
   float getAverageEventWeight() const ;
   float getTotalWeightedCount() const ;
   float getAverageTotalWeight() const ;
   float getExpectedYield( float ) const ;
   void  makeBasicPlots();

private:
   std::string  _name;
   TChain*      _chain;
   Color_t      _fillColor;
   Color_t      _lineColor;
   HistMap      _histMap;
   float        _cross_section;
   float        _selection_eff;
   float        _sample_weight;
  
   //----- ROOT object interaction helper functions  ------------------------------
   void addHist( const std::string& , int ,  float , float );
   void printFileList() const;
};

#endif // __SAMPLEINFO_H__
