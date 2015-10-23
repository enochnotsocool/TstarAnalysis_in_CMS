/*******************************************************************************
 *
 *  Filename    : SampleInfo.h
 *  Description : Define class of sample ntuple file class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __SAMPLEINFO_H__
#define __SAMPLEINFO_H__

#include <vector>
#include <string>
#include "TChain.h"
#include "TH1F.h"
typedef std::vector<const std::string>  stringList;

class SampleInfo {
public:
   SampleInfo( const std::string& );
   virtual ~SampleInfo ();

   void  addFile( const std::string& );
   void  setTargetEventCount( const float );
   float getStatisticsWeight() const ;
   void  setPlotStyle( const std::string& );
   const std::string& plotStyle() const ;

   void  makeBasicPlots();
   TH1F* chimassHist();
   TH1F* jetPtHist();
private:
   std::string  _name;
   std::string  _plotstyle;
   float        _targetEventCount;

   TChain* _chain;
   TH1F*   _chimass;
   TH1F*   _jetPt;

};


#endif // __SAMPLEINFO_H__
