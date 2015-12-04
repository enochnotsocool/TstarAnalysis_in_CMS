/*******************************************************************************
 *
 *  Filename    : Utils.cc
 *  Description : Implementation of Utils functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "TH1F.h"

void FillHistAtBin( TH1F* hist , int& counter )
{
   if( hist != NULL ){ hist->Fill( counter ); }
   ++counter;
}
