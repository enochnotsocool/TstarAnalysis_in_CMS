/*******************************************************************************
 *
 *  Filename    : AnalysisMgr.h
 *  Description : Plot Merging class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#ifndef __ANALYSISMGR_H__
#define __ANALYSISMGR_H__

#include <map>
#include <string>
#include "SampleMgr.h"
#include "PlotDef.h"
#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"

typedef std::pair<const std::string, SampleMgr*> SamplePair;
typedef std::map<const std::string, SampleMgr*>  SampleMap ; 

class AnalysisMgr {
public:
   AnalysisMgr( const std::string& );
   virtual ~AnalysisMgr ();

   void Print() const;
   void printAllSamples() const ;
   void printSample( const std::string& ) ;
   void setLumi( const float );
   bool setSignalMass( const std::string& );
   SampleMgr* sample( const std::string& );
   void makeBasicPlots();
   void makeDataToBGPlot( const std::string& );
   void makeSignalPlot( const std::string& );

private:
   TFile*     _outputFile;
   SampleMap  _MCsignalMap; 
   SampleMap  _MCbackgroundMap;
   SampleMgr* _dataSample;
   SampleMgr* _currentSignal;
   //----- Variables for combined plotting  ---------------------------------------
   TCanvas*   _canvas;
   THStack*   _stackHist;
   TLegend*   _combineLegend;
   TLegend*   _signalLegend;
   float      _totalLumi;

   //----- Helper function for constructor  ---------------------------------------
   void initSamples();

   //----- Helper function for combined plotting  ---------------------------------
   const  std::string makeHistTitle( const std::string& ) const;
   void   addMCToStack( SampleMgr* , const std::string& );
   float  getHistScale( SampleMgr* ) const;
};

#endif // __ANALYSISMGR_H__

