/*******************************************************************************
 *
 *  Filename    : Counting.h
 *  Description : Header for helping with counting
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#ifndef __COUNTING_H__
#define __COUNTING_H__

#include "TH1F.h"
#define HIST_COUNT( N ) \
   if( hist!=0 ){ hist->Fill(N); }


#endif // __COUNTING_H__
