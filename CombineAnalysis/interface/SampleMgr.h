/*******************************************************************************
 *
 *  Filename    : SampleMgr.h
 *  Description : Define class of sample ntuple file class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __SAMPLEINFO_H__
#define __SAMPLEINFO_H__

#include "CMSSW_Utils/Utils_Types/interface/Parameter.h"
#include "TstarAnalysis/CombineAnalysis/interface/HistMgr.h"
#include "TstarAnalysis/RootFormat/interface/MiniEvent.h"

#include <string>
#include <vector>
#include <TChain.h>
#include <TH1F.h>


class SampleMgr {
public:
   SampleMgr( const std::string& , const std::string& );
   SampleMgr( const SampleMgr& );
   virtual ~SampleMgr ();

   //----- Basic access functions  ------------------------------------------------
   const std::string& Name()         const { return _name; }
   const std::string  LatexName()    const { return MakeLatexName(); }
   const std::string  RootName()     const { return MakeRootTitle(); }
   const Parameter&   CrossSection() const { return _cross_section; }
   const Parameter&   SelectionEff() const { return _selection_eff; }
   const Parameter&   SampleWeight() const { return _sample_weight; }
  
   double    GetRawEventCount()      const ;
   double    GetWeightedEventCount() const;
   double    GetHistogramScale( const double ) const ; 
   Parameter ExpectedYield( const double ) const ;

   void SetCrossSection( const Parameter& x ) { _cross_section = x ; }
   void SetSelectionEff( const Parameter& x ) { _selection_eff = x ; }
   void SetSampleWeight( const Parameter& x ) { _sample_weight = x ; }
   
   TH1F*       Hist( const std::string& x ) { return _histList[x](); }
   const TH1F* Hist( const std::string& x ) const {  return _histList[x](); }

   //----- ROOT Object interaction (SampleMgr.cc)  --------------------------------
   void  AddFile( const std::string& );
   void  SetLineColor( const Color_t& );
   void  SetFillColor( const Color_t& , const float );

   //----- Analysis specific funtions (SampleMgr_Compute.cc)  ---------------------
   void  MakeBasicPlots();

private:
   const std::string      _name;
   const std::string      _latex_name;
   HistList         _histList;
   Parameter        _cross_section;
   Parameter        _selection_eff;
   Parameter        _sample_weight;
   mutable double  _rawEventsCount;
   mutable double  _eventWeightCount;
   
   //----- File Reading data members  ---------------------------------------------
   TChain*          _chain;
   MiniEvent*       _event;

   //----- ROOT object interaction helper functions  ------------------------------
   void printFileList() const;
   const std::string MakeRootTitle() const ;
   const std::string MakeLatexName() const ;
};

#endif // __SAMPLEINFO_H__

