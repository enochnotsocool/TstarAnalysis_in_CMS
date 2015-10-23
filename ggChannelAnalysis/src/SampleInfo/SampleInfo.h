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
#include <map>
#include "TChain.h"
#include "TH1F.h"

typedef std::vector<const std::string>  stringList;
typedef std::map<const std::string, TH1F*>  HistMap; 

class SampleInfo {
public:
   SampleInfo( const std::string& );
   virtual ~SampleInfo ();

   void  addFile( const std::string& );
   void  setTargetEventCount( const float );
   float getStatisticsWeight() const ;

   TH1F* Hist( const std::string& );
   void  HistPlot( const std::string& , const std::string& );
   void  makeBasicPlots();

   const std::string& plotStyle() const ;
   void  setPlotStyle( const std::string& );
   void  addPlotStyle( const std::string& );
   void  setFillColor( const Color_t , const float=1.0 );
   void  setLineColor( const Color_t );
private:
   std::string  _name;
   std::string  _plotstyle;
   HistMap      _histMap;
   float        _targetEventCount;
   
   TChain*      _chain;

   void addHist( const std::string& , int ,  float , float );
};


#endif // __SAMPLEINFO_H__
