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
   T_PLUS_BOSON_FIRST = 1,
   T_PLUS_BOSON_LAST   = 4,

   WJets_HT100_200    = 11,
   WJets_HT200_400    = 12,
   WJets_HT400_600    = 13,
   WJets_HT600_800    = 14,
   WJets_HT800_1200   = 15,
   WJets_HT1200_2500  = 16,
   WJets_HT2500_Inf   = 17,
   ZJets_HT100_200    = 18,
   ZJets_HT200_400    = 19,
   ZJets_HT400_600    = 20,
   ZJets_HT600_Inf    = 21,
   SINGLE_BOSON_FIRST = 11,
   SINGLE_BOSON_LAST  = 21,

   WW    = 22,
   WZ    = 23,
   ZZ    = 24,
   DI_BOSON_FIRST = 22,
   DI_BOSON_LAST   = 24,

   BOSON_FIRST = SINGLE_BOSON_FIRST,
   BOSON_LAST  = DI_BOSON_LAST,

   SingleT_S = 31,
   SingleT_T = 32,
   SingleT_TW = 33,
   SingleTbar_TW = 34,
   SINGLE_T_FIRST = 31,
   SINGLE_T_LAST = 34,

   TTJets = 41,
   
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
   SIGNAL_FIRST = Tstar_M1600,
   SIGNAL_LAST  = Tstar_M0700,
   SIGNAL_END = -11,
   
   // Data 
   Data = 1000,

   DUMMY_END = 1000000
};
extern std::string Stringify( const SampleName );
extern SampleName SampleFromString( const std::string& );
extern std::string LatexName( const SampleName );
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
