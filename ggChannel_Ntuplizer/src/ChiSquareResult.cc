/*******************************************************************************
 *
 *  Filename    : ChiSquareResult.cc
 *  Description : Implementations of ChiSquare Results
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/ggChannel_Ntuplizer/interface/ChiSquareSolver.h"

ChiSquareResult::ChiSquareResult( double tstar, double chisq ):
   _tstarMass( tstar ) , 
   _chiSquare( chisq )
{}

ChiSquareResult::~ChiSquareResult(){}


double ChiSquareResult::TstarMass() const { return _tstarMass; }
double ChiSquareResult::ChiSquare() const { return _chiSquare; }
