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
   
   // Plotting commands
   void MakeBasicPlots();
   void MakeDataToBGPlot( const PlotName& );
   void MakeSignalPlot( const PlotName& );
   void MakeInSampleComparison( const SampleName&, const PlotName&, const PlotName& );

   // Limit-Calculation
   void MakeLimitProcesses( std::vector<const HC_Process*>& );

   // File Reading functions 
   void ParseCMDFile( const std::string& filename );
   void SetCrossSections( const std::string& filename );
   void SetSelectionEfficiency( const std::string& filename );
   void SetSampleWideWeights( const std::string& filename );
   void SetSampleInputs( const std::string& filename );


private:
   ChannelName _name;
   SampleMap   _MCsignalMap; 
   SampleMap   _MCbackgroundMap;
   SampleMgr*  _dataSample;
   SampleMgr*  _currentSignal;
   
   //----- Variables for combined plotting  ---------------------------------------
   static float _totalLumi = 0. ;

   //----- Helper function for constructor  ---------------------------------------
   void initSamples();

   //----- Data to BC comparison plot  --------------------------------------------
   TFile* openPlotFile() const;
   const  std::string makeHistTitle( const PlotName& ) const;
   void   makeBGStack( THStack*, TH1F*, TH1F*, const PlotName& ) const;
   void   makeDataBGRatio(TH1F*, const TH1F*, const TH1F* ) const; 
   void   setFontStyle( TH1F* ) const;
   void   setXAxisFont( TH1F* ) const;
   void   matchHeights( TH1F*, TH1F* ) const;
   void   makeCombinedLegend( TLegend*, const TH1F*, const PlotName& );
   float  getHistScale( const SampleMgr* ) const;


   //----- Signal Channel Plots  --------------------------------------------------
   void makeSignalLegend( TLegend*, const PlotName& );
};

#endif // __CHANNELMGR_H__

