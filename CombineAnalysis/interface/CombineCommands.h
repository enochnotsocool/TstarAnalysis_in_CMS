/*******************************************************************************
 *
 *  Filename    : CombineCommands.h
 *  Description : Defining all derived classes of CombineCMDs
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __COMBINECOMMANDS_H__
#define __COMBINECOMMANDS_H__

#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"


//----- Sample initializing functions  -----------------------------------------
DEFINE_CMD( SetSelectionEfficiency );
DEFINE_CMD( SetSampleWideWeight );
DEFINE_CMD( SetSampleInput );

DEFINE_CMD( MakeBasicPlots );
DEFINE_CMD( MakeDataBGPlot );
DEFINE_CMD( MakeSignalPlot );
DEFINE_CMD( MakeLatexSummary );

DEFINE_CMD( MakeLimitRequirement );
DEFINE_CMD( RunCombine );
DEFINE_CMD( WaitCMD );
DEFINE_CMD( MakeLimitPlot );

#endif // __COMBINECOMMANDS_H__

