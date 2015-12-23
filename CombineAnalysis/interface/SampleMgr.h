/*******************************************************************************
 *
 *  Filename    : SampleMgr.h
 *  Description : Define class of sample ntuple file class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __SAMPLEINFO_H__
#define __SAMPLEINFO_H__

#include <string>
#include <map>
#include <TChain.h>
#include <TH1F.h>
#include "TstarAnalysis/CombineAnalysis/interface/PlotDef.h"
#include "TstarAnalysis/CombineAnalysis/interface/Parameter.h"

typedef std::map<const PlotName,TH1F*>  HistMap; 

enum SampleName { 
   // Background MC
   TTW_Lepton = 0,
   TTW_Quark  = 1,
   TTZ_Lepton = 2,
   TTZ_Quark  = 3,

   WJets = 10,
   ZJets = 11,
   WW    = 12,
   WZ    = 13,
   ZZ    = 14,

   SingleT_S = 20,
   SingleT_T = 21,
   SingleT_TW = 22,
   SingleTbar_TW = 23,

   TTJets = 30,
   
   // Single MC
   Tstar_M0700 = 100,
   Tstar_M0800 = 101,
   Tstar_M0900 = 102, 
   Tstar_M1000 = 103,
   Tstar_M1100 = 104,
   Tstar_M1200 = 105,
   Tstar_M1300 = 106,
   Tstar_M1400 = 107,
   Tstar_M1500 = 108,
   Tstar_M1600 = 109,
   
   // Data 
   Data = 1000,

   DUMMY_END
};

extern std::string Stringify( const SampleName );
SampleName SampleFromString( const std::string& );

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
   TChain*      _chain;
   Color_t      _fillColor;
   Color_t      _lineColor;
   HistMap      _histMap;
   Parameter    _cross_section;
   Parameter    _selection_eff;
   Parameter    _sample_weight;
  
   //----- ROOT object interaction helper functions  ------------------------------
   void addHist( const PlotName& , int ,  float , float );
   void printFileList() const;
};

#endif // __SAMPLEINFO_H__

