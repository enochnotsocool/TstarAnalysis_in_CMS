/*******************************************************************************
 *
 *  Filename    : SampleMgr.h
 *  Description : Define class of sample ntuple file class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __SAMPLEINFO_H__
#define __SAMPLEINFO_H__

#include "TstarAnalysis/CombineAnalysis/interface/PlotDef.h"
#include "TstarAnalysis/CombineAnalysis/interface/Parameter.h"
#include "TstarAnalysis/RootFormat/interface/MiniEvent.h"
#include "TstarAnalysis/RootFormat/interface/ChiSquareResult.h"
#include "TstarAnalysis/RootFormat/interface/HitFitResult.h"

#include <string>
#include <map>
#include <TChain.h>
#include <TH1F.h>

typedef std::map<const PlotName,TH1F*>  HistMap; 

class SampleMgr {
public:
   SampleMgr( const SampleName& );
   virtual ~SampleMgr ();

   //----- Basic info functions  --------------------------------------------------
   const SampleName& name() const;
   const std::string NameString() const{ return Stringify(_name); }
   float crossSection() const ;
   void  setCrossSection( const Parameter& ) ;
   float selectionEff() const ;
   void  setSelectionEff( const Parameter& ) ;
   float sampleWeight() const ;
   void  setSampleWeight( const float );
   void  Print(const float) const;
   void  PrintTable(const float) const;

   //----- ROOT object interaction  -----------------------------------------------
   void  addFile( const std::string& );
   TH1F* Hist( const PlotName& );
   const TH1F* Hist( const PlotName& ) const;
   void  setColor( const Color_t& );
   void  setLineColor( const Color_t& );
   void  setFillColor( const Color_t& , const float=1.0 );

   //----- Computation functions  -------------------------------------------------
   float getRawEventCount() const;
   float getEventWeightedCount() const ;
   float getAverageEventWeight() const ;
   float getTotalWeightedCount() const ;
   float getAverageTotalWeight() const ;
   Parameter getExpectedYield( float ) const ;
   void  makeBasicPlots();

private:
   SampleName   _name;
   Color_t      _fillColor;
   Color_t      _lineColor;
   HistMap      _histMap;
   Parameter    _cross_section;
   Parameter    _selection_eff;
   Parameter    _sample_weight;
   mutable double  _rawEventsCount;
   mutable double  _eventWeightCount;
   
   //----- File Reading data members  ---------------------------------------------
   TChain*          _chain;
   MiniEvent*       _event;
   ChiSquareResult* _chisq;
   HitFitResult*    _hitfit;

   //----- ROOT object interaction helper functions  ------------------------------
   void addHist( const PlotName& , int ,  float , float );
   void printFileList() const;
};

#endif // __SAMPLEINFO_H__

