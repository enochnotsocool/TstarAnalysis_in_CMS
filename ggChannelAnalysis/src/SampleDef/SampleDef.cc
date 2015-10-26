/*******************************************************************************
 *
 *  Filename    : SampleDef.cc
 *  Description : String definition for sample getting
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "SampleDef.h"

const std::string samplename[SAMPLE_NAME_COUNT] = {
   "Data",                     // DATA = 0 ,
   "Tstar",                    // TSTAR = 1 ,
   "TTJets" ,                  // TTJETS = 2,
   "SingleT_Schannel" ,        // SINGLET_SCHANNEL = 3 ,
   "SingleT_Tchannel_top" ,    // SINGLET_TCHANNEL_TOP = 4 ,
   "SingleT_Tchannel_antitop", // SINGLET_TCHANNEL_ANTITOP = 5,
   "SingleT_TWchannel_top",    // SINGLET_TWCHANNEL_TOP = 6,
   "SingleT_TWchannel_antitop" // SINGLET_TWCHANNEL_ANTITOP = 7 ,
};

const std::string plotname[PLOT_NAME_COUNT] = {
   "ChiSquareMass" , // CHI_SQR_MASS = 0 ,
   "JetPt"           // JET_PT       = 1 ,
};

const unsigned int binCount[PLOT_NAME_COUNT] = {
   50 , 
   50
};

const unsigned int histMax[PLOT_NAME_COUNT] = {
   2000 , 
   600 
};

