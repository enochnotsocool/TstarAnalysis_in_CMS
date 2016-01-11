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

#include "TstarAnalysis/CombineAnalysis/interface/Enums.h"
#include "TstarAnalysis/CombineAnalysis/interface/SampleMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/PlotDef.h"
#include "TstarAnalysis/CombineAnalysis/interface/Parameter.h"
#include "TstarAnalysis/CombineAnalysis/interface/HC_Process.h"
#include "TstarAnalysis/CombineAnalysis/interface/NuisancePar.h"
#include <map>
#include <string>
#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"

typedef std::pair<const SampleName, SampleMgr*> SamplePair;
typedef std::map<const SampleName, SampleMgr*>  SampleMap ; 

class ChannelMgr {
public:
   ChannelMgr( const ChannelName );
   virtual ~ChannelMgr ();

   ChannelName Name() const { return _name; }
   void Print() const;
   void printAllSamples() const ;
   void printTable() const ;
   void printSample( const SampleName& ) ;
   void setLumi( const float );
   bool setSignalMass( const SampleName& );
   SampleMgr* sample( const SampleName& );
   const SampleMgr* sample( const SampleName& ) const;

   // Saving histograms
   void MakeBasicPlots();
 
   // Plotting commands
   void MakeDataToBGPlot( const PlotName& ) const ;
   void MakeSignalPlot( const PlotName& ) const ;
   void MakeInSampleComparison( const SampleName&, const PlotName&, const PlotName& ) const;

   // Limit-Calculation
   void MakeLimitRequirement( const SampleName& );
   void RunCombine( const SampleName&, const std::string& );
   void MakeLimitPlot() const;
   std::string shapeFileName( const SampleName& ) const ;
   std::string cardFileName( const SampleName& ) const ;

   // File Reading functions 
   void SetCrossSection( const std::string& filename );
   void SetSelectionEfficiency( const std::string& filename );
   void SetSampleWideWeight( const std::string& filename );
   void SetSampleInput( const std::string& filename );


private:
   //------------------------------------------------------------------------------ 
   //   Private data members
   //------------------------------------------------------------------------------
   ChannelName _name;
   SampleMap   _MCsignalMap; 
   SampleMap   _MCbackgroundMap;
   SampleMgr*  _dataSample;
   SampleMgr*  _currentSignal;
   static float _totalLumi;
  
   std::vector<const HC_Process*>  _processList;
   std::map<const NuisancePar,std::map<const HC_Process*,float> > _uncertaintlyList;


   //------------------------------------------------------------------------------ 
   //   Private member functions
   //------------------------------------------------------------------------------

   //----- Helper function for constructor  ---------------------------------------
   void initSamples();

   //----- Data to BC comparison plot  --------------------------------------------
   const std::string plotfilepath( const std::string& ) const;
   const std::string makeHistTitle( const PlotName& ) const;
   void  makeBGStack( THStack*& , TH1F*& , TH1F*& , const PlotName& ) const;
   void  makeDataBGRatio(TH1F*&, const TH1F*, const TH1F* ) const; 
   void  setFontStyle( THStack* ) const ;
   void  setFontStyle( TH1F* ) const;
   void  setXAxisFont( TH1F* ) const;
   void  matchHeights( TH1F*, TH1F* ) const;
   void  makeCombinedLegend( TLegend*, const TH1F*, const PlotName& ) const ;
   float getHistScale( const SampleMgr* ) const;

   //----- Signal Channel Plots  --------------------------------------------------
   void makeSignalLegend( TLegend*, const PlotName& ) const;

   //----- Limit calculation helper functions  ------------------------------------
   // Data type management
   void makeProcessList( const SampleName& );
   void makeNuissanceList();
   void makeSignalProcess( HC_Process* const );
   void makeBGLimitProcess( HC_Process* const, const SampleName&, const SampleName&);
   void normalizeProcessShape( HC_Process* const );
   
   // File writing 
   void makeShapeFile(const SampleName& ) const ;
   void makeCard_Header(const SampleName&) const ;
   void makeCard_ShapeMarker(const SampleName&) const ;
   void makeCard_ChannelYield(const SampleName&) const ;
   void makeCard_ProcessYield(const SampleName&) const ;
   void makeCard_NuissanceTable(const SampleName&) const ;
   void clearList();
   
   int  MassNumber( const SampleName& )const;
   std::string MassNumberString( const SampleName& )const;
   std::string raw_combineoutput( const SampleName& , const std::string& )const;
   std::string store_combineoutput( const SampleName&, const std::string& )const;
};


#endif // __CHANNELMGR_H__

