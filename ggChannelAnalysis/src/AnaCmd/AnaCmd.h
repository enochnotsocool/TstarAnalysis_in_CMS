/*******************************************************************************
 *
 *  Filename    : plotCmd.h
 *  Description : Definition of all plot commands
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __PLOTCMD_H__
#define __PLOTCMD_H__

#include "cmdParser.h"

CmdClass(SetFileBase);
CmdClass(SetLumi);
CmdClass(Print);
CmdClass(AddFile);
CmdClass(SetXSection);
CmdClass(SetEff);
CmdClass(SetSignal);
CmdClass(MakeBasic);
CmdClass(MakeCombine);
CmdClass(ClearPlot);
#endif // __PLOTCMD_H__
