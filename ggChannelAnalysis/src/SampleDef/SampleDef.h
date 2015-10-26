/*******************************************************************************
 *
 *  Filename    : SampleDef.h
 *  Description : Sample definition
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef __SAMPLEDEF_H__
#define __SAMPLEDEF_H__

#include <string>

enum SAMPLE_NAME : uint16_t { 
   DATA                      = 0 ,
   TSTAR                     = 1 ,
   TTJETS                    = 2 ,
   SINGLET_SCHANNEL          = 3 ,
   SINGLET_TCHANNEL_TOP      = 4 ,
   SINGLET_TCHANNEL_ANTITOP  = 5 ,
   SINGLET_TWCHANNEL_TOP     = 6 ,
   SINGLET_TWCHANNEL_ANTITOP = 7 ,

   SAMPLE_NAME_COUNT = 8
};

enum PLOT_NAME : uint16_t { 
   CHI_SQR_MASS = 0 ,
   JET_PT       = 1 ,

   PLOT_NAME_COUNT = 2 
};

extern const std::string samplename[SAMPLE_NAME_COUNT];
extern const std::string plotname[PLOT_NAME_COUNT];
extern const unsigned int binCount[PLOT_NAME_COUNT];
extern const unsigned int histMax[PLOT_NAME_COUNT];

#endif // __SAMPLEDEF_H__
