/*******************************************************************************
 *
 *  Filename    : Enums.h
 *  Description : Listing all Enums, as well as enum-string conversion functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __ENUMS_H__
#define __ENUMS_H__

#include <string>
//------------------------------------------------------------------------------ 
//   Plot Related enumerators
//------------------------------------------------------------------------------
enum PlotName 
{
   JetCount           = 0,
   JetPt              = 1,
   JetEta             = 2,
   LeptonPt           = 10,
   LeptonEta          = 11,
   MET                = 20,
   VertexCount        = 21,

   ChiSquareTstarMass = 50,
   ChiSquareTMass     = 51,

   HitFitTstarMass    = 60,
   HitFitTMass        = 61 ,

   PLOTNAME_END
};
extern std::string  Stringify( const PlotName );
extern PlotName     PlotNameFromString( const std::string& );
extern bool CheckPlotName( const PlotName );

//------------------------------------------------------------------------------ 
//   Sample Related enumerators
//------------------------------------------------------------------------------
enum SampleName 
{ 
   // Background MC
   TTW_Lepton = 1,
   TTW_Quark  = 2,
   TTZ_Lepton = 3,
   TTZ_Quark  = 4,
   TT_PLUS_BOSON = 5,

   WJets = 11,
   ZJets = 12,
   WW    = 13,
   WZ    = 14,
   ZZ    = 15,
   BOSONS = 16,

   SingleT_S = 21,
   SingleT_T = 22,
   SingleT_TW = 23,
   SingleTbar_TW = 24,
   SINGLE_T = 25,

   TTJets = 31,
   
   // Single MC
   Tstar_M0700 = -1,
   Tstar_M0800 = -2,
   Tstar_M0900 = -3, 
   Tstar_M1000 = -4,
   Tstar_M1100 = -5,
   Tstar_M1200 = -6,
   Tstar_M1300 = -7,
   Tstar_M1400 = -8,
   Tstar_M1500 = -9,
   Tstar_M1600 = -10,
   SIGNAL_END = -11,
   
   // Data 
   Data = 1000,

   DUMMY_END = 1000000
};
extern std::string Stringify( const SampleName );
extern SampleName SampleFromString( const std::string& );
extern bool SignalSample( const SampleName );


//------------------------------------------------------------------------------ 
//   Channel Names
//------------------------------------------------------------------------------
enum ChannelName 
{ 
   ggMuon = 0,

   CHANNEL_END 
};
extern std::string Stringify( const ChannelName );
extern ChannelName ChannelFromString( const std::string& );

#endif // __ENUMS_H__
