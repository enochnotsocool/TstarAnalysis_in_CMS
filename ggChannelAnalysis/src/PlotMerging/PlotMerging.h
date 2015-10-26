/*******************************************************************************
 *
 *  Filename    : PlotMerging.h
 *  Description : Plot Merging class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     :
 *
*******************************************************************************/
#ifndef __PLOTMERGING_H__
#define __PLOTMERGING_H__

#include <map>
#include <string>
#include "SampleInfo.h"
#include "SampleDef.h"

#include "TFile.h"
#include "THStack.h"
#include "TCanvas.h"

typedef std::map<const std::string, SampleInfo*> SampleMap ; 

class PlotMerging {
public:
   PlotMerging( const std::string& );
   virtual ~PlotMerging ();

   void makePlot( const std::string& );
private:
   TFile*     _outputFile;
   SampleMap  _sampleMap; 
   THStack*   _stackHist;
   TCanvas*   _canvas;

   void InitSampleStyles();
};

#endif // __PLOTMERGING_H__
