/*******************************************************************************
 *
 *  Filename    : SampleDef.h
 *  Description : Declaring all samples as global objects
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Actual objects and initialization are performed in SampleInfo/SampleDef.cc
 *
*******************************************************************************/
#ifndef __SAMPLEDEF_H__
#define __SAMPLEDEF_H__

#include "SampleInfo.h"
extern SampleInfo Data;
extern SampleInfo Tstar_Signal;
extern SampleInfo TTJets_background ; 
extern SampleInfo SingleT_s_channel;
extern SampleInfo SingleT_t_channel_top;
extern SampleInfo SingleT_t_channel_antitop;
extern SampleInfo SingleT_tW_channel_top;
extern SampleInfo SingleT_tW_channel_antitop;

extern void InitSamples();

#endif // __SAMPLEDEF_H__
