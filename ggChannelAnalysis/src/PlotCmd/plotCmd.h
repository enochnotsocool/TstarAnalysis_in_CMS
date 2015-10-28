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
CmdClass(AddType);
CmdClass(AddFile);
CmdClass(SetColor);
CmdClass(SetLine);
CmdClass(MakePlot);

#endif // __PLOTCMD_H__
