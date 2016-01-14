/*******************************************************************************
 *
 *  Filename    : ChannelMgr.h
 *  Description : Plot Merging class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#ifndef __CHANNELMGR_H__
#define __CHANNELMGR_H__

#include "TstarAnalysis/CombineAnalysis/interface/HistMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/SampleMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/SampleListing.h"
#include "TstarAnalysis/CombineAnalysis/interface/HC_Process.h"
#include "TstarAnalysis/CombineAnalysis/interface/NuisancePar.h"
#include <map>
#include <string>
#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"

class ChannelMgr {
public:
   ChannelMgr( const std::string& , const std::string& );
   virtual ~ChannelMgr ();

   //----- Access functions  ------------------------------------------------------
   const std::string& Name()      const { return _name; }
   const std::string  RootName()  const { return MakeRootName(); }
   const std::string  LatexName() const { return MakeLatexName(); }
   SampleMgr& Sample( const std::string& );
   const SampleMgr& Sample( const std::string& ) const;
   bool  HasSample(const std::string& ) const;
   bool  HasSample( const std::string&, const std::string& )const;
   void SetLumi( const double x ){ _totalLumi = x; }
   
   //----- Calling Sample Functions  ----------------------------------------------
   void MakeBasicPlots();

   //----- Initializing by files (ChannelMgr_ReadFile.cc)  ------------------------
   void SetSelectionEfficiency( const std::string& filename );
   void SetSampleWeight( const std::string& filename );
   void SetSampleInput( const std::string& filename );
   void SetSampleColor( const std::string& filename );

   //----- Making Latex Outputs (ChannelMgr_Latex.cc)  ----------------------------
   void MakeLatexSummary() const;

   //----- Validation Plots (ChannelMgr_Validation.cc  ----------------------------
   void MakeDataBGPlot( const std::string& ) const ;
   void MakeSignalPlot( const std::string& ) const ;

   void MakeLimitRequirement( const std::string& ); // ChannelMgr_HiggsCombine.cc
   void RunCombine( const std::string&, const std::string& ); // ChannelMgr_RunCombine.cc
   void MakeLimitPlot() const;

   // File Reading functions 

private:
   //------------------------------------------------------------------------------ 
   //   Private data members
   //------------------------------------------------------------------------------
   const std::string  _name;
   const std::string  _latex_name;
   static float _totalLumi;

   SampleMgr   _dataSample;
   SampleTable _MCSampleTable;

   std::vector<const HC_Process*> _processList;
   std::map<const NuisancePar,std::map<const HC_Process*,Parameter>> _nuissanceMap;

   //----- Self Access functions  -------------------------------------------------
   const std::string MakeRootName() const;
   const std::string MakeLatexName()const;

   //----- Storage file naming functions(ChannelMgr_Save.cc)  ---------------------
   const std::string SummaryFileName() const;
   const std::string PlotFilePath( const std::string& ) const;
   const std::string ShapeFilePath( const std::string& ) const;
   const std::string CardeFilePath( const std::string& ) const ;
   const std::string RawCombineOutput( const std::string& , const std::string& )const;
   const std::string StoreCombineOutput( const std::string&, const std::string& )const;
   const std::string MassNumberString( const std::string& )const;

   //----- Validation Plots (ChannelMgr_Validation.cc)  ---------------------------
   void  MakeBGStack( THStack*& , TH1F*& , TH1F*& , const std::string& ) const;
   void  MakeDataBGRatio(TH1F*&, const TH1F*, const TH1F* ) const; 
   void  MakeCombinedLegend( TLegend*, const TH1F*, const std::string& ) const ;

   //----- Signal Channel Plots  --------------------------------------------------
   void makeSignalLegend( TLegend*, const std::string& ) const;

   //----- Limit calculation helper functions  ------------------------------------
   const HC_Process* MakeSignalProcess( const std::string& ) const;
   const HC_Process* MakeBGProcess( const SampleList& ) const ;
   void MakeNuissanceMap();
   void MakeShapeFile( const std::string& ) const ;
   void MakeCardFile( const std::string& ) const;
   void clearList();
   
   //----- Latex Related Helper functions (ChannelMgr_Latex.cc)  ------------------
   void SummaryHeader() const;
   void SummarySection( const SampleList& ) const;
   void SummaryEnd() const;
};


#endif // __CHANNELMGR_H__

