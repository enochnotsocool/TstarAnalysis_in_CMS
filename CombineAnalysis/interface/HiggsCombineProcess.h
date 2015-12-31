/*******************************************************************************
 *
 *  Filename    : HiggsCombineProcess.h
 *  Description : Define a process to be passed onto HiggsCombine package
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __HIGGSCOMBINEPROCESS_H__
#define __HIGGSCOMBINEPROCESS_H__

#include "Parameter.h"
#include "UncertaintyList.h"

class HiggsCombineProcess
{
public:
   HiggsCombineProcess();
   virtual ~HiggsCombineProcess ();

private:
   ChannelName _channelName;
   ProcessName _processName;
   double      _expectedYeild;
      
};

#endif // __HIGGSCOMBINEPROCESS_H__
