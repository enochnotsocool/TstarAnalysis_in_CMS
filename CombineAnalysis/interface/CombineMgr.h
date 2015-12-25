/*******************************************************************************
 *
 *  Filename    : CombineMgr.h
 *  Description : Plot Merging class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#ifndef __COMBINEMGR_H__
#define __COMBINEMGR_H__

#include <map>
#include <string>
#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TstarAnalysis/CombineAnalysis/interface/SampleMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/PlotDef.h"
#include "TstarAnalysis/CombineAnalysis/interface/Parameter.h"

typedef std::pair<const SampleName, SampleMgr*> SamplePair;
typedef std::map<const SampleName, SampleMgr*>  SampleMap ; 

class CombineMgr {
public:
   CombineMgr( const std::string& );
   virtual ~CombineMgr ();

   void Print() const;
   void printAllSamples() const ;
   void printTable() const ;
   void printSample( const SampleName& ) ;
   void setLumi( const float );
   bool setSignalMass( const SampleName& );
   SampleMgr* sample( const SampleName& );
   void MakeBasicPlots();
   void MakeDataToBGPlot( const PlotName& );
   void MakeSignalPlot( const PlotName& );
   void MakeInSampleComparison( const SampleName&, const PlotName&, const PlotName& );

   // File Reading functions 
   void ParseCMDFile( const std::string& filename );
   void SetCrossSections( const std::string& filename );
   void SetSelectionEfficiency( const std::string& filename );
   void SetSampleWideWeights( const std::string& filename );
   void SetSampleInputs( const std::string& filename );


private:
   TFile*     _outputFile;
   SampleMap  _MCsignalMap; 
   SampleMap  _MCbackgroundMap;
   SampleMgr* _dataSample;
   SampleMgr* _currentSignal;
   
   //----- Variables for combined plotting  ---------------------------------------
   TCanvas*   _canvas;
   THStack*   _stackHist;
   TH1F*      _totalHist; // For error computation
   TH1F*      _relErrHist;
   TLegend*   _combineLegend;
   TLegend*   _signalLegend;
   float      _totalLumi;

   //----- Helper function for constructor  ---------------------------------------
   void initSamples();

   //----- Data to BC comparison plot  --------------------------------------------
   const  std::string makeHistTitle( const PlotName& ) const;
   void   addMCToStack( SampleMgr* , const PlotName& );
   float  getHistScale( SampleMgr* ) const;
   void   initTotalHist( const PlotName& ) ;
   void   makeCombinedLegend( const PlotName& );
   void   setCombinedTotalErrors();
   void   setCombinedRelativeErrors();

   //----- Signal Channel Plots  --------------------------------------------------
};

#endif // __COMBINEMGR_H__

