/*******************************************************************************
 *
 *  Filename    : Available.cc
 *  Description : Setting Available plots
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/PlotDef.h"

//------------------------------------------------------------------------------ 
//   Declaring global object instance
//------------------------------------------------------------------------------
PlotList  availiablePlots;

//------------------------------------------------------------------------------ 
//   Initializing available Plot List
//------------------------------------------------------------------------------
bool initPlotList()
{
   availiablePlots.insert( PlotPair( ChiSquareMass , PlotDef() ));
   availiablePlots[ChiSquareMass].setBinCount( 29 );
   availiablePlots[ChiSquareMass].setXMax( 3000. );
   availiablePlots[ChiSquareMass].setXMin( 100.  );
   availiablePlots[ChiSquareMass].setTitle( "Mass of tg system"  );
   availiablePlots[ChiSquareMass].setXtitle( "M_{tg} (GeV/c^{2})" );
   availiablePlots[ChiSquareMass].makeYtitle( "GeV/c^{2}" );

   availiablePlots.insert( PlotPair( MET , PlotDef() ));
   availiablePlots[MET].setBinCount( 30 );
   availiablePlots[MET].setXMax( 600. );
   availiablePlots[MET].setXMin( 0. );
   availiablePlots[MET].setTitle( "Missing Transverse Energy" );
   availiablePlots[MET].setXtitle( "M_{E_{T}} (GeV)");
   availiablePlots[MET].makeYtitle( "GeV" );

   availiablePlots.insert( PlotPair( JetPt , PlotDef() ));
   availiablePlots[JetPt].setBinCount( 30 );
   availiablePlots[JetPt].setXMax( 600. );
   availiablePlots[JetPt].setXMin( 0.   );
   availiablePlots[JetPt].setTitle( "Leading Jet p_{T}"   );
   availiablePlots[JetPt].setXtitle( "p_{t}  (GeV/c)" );
   availiablePlots[JetPt].makeYtitle( "GeV/c" );
   
   availiablePlots.insert( PlotPair( JetEta , PlotDef() ));
   availiablePlots[JetEta].setBinCount( 24 );
   availiablePlots[JetEta].setXMin(-2.4);
   availiablePlots[JetEta].setXMax( 2.4);
   availiablePlots[JetEta].setTitle( "Leading Jet #eta");
   availiablePlots[JetEta].setXtitle("Jet #eta");
   availiablePlots[JetEta].makeYtitle("");
   
   /*
   availiablePlots.insert( PlotPair( "JetCount" , PlotDef() ));
   availiablePlots["JetCount"].setBinCount( 10 );
   availiablePlots["JetCount"].setXMax( 15. );
   availiablePlots["JetCount"].setXMin( 5.   );
   availiablePlots["JetCount"].setTitle( "No. of Events with N Jets" );
   availiablePlots["JetCount"].setXtitle( "No. of Jets" );
   availiablePlots["JetCount"].makeYtitle( "" );
   */

   availiablePlots.insert( PlotPair( LeptonPt , PlotDef() ));
   availiablePlots[LeptonPt].setBinCount( 30 );
   availiablePlots[LeptonPt].setXMax( 600. );
   availiablePlots[LeptonPt].setXMin( 0.   );
   availiablePlots[LeptonPt].setTitle( "Lepton p_{T}"   );
   availiablePlots[LeptonPt].setXtitle( "lepton p_{t}  (GeV/c)" );
   availiablePlots[LeptonPt].makeYtitle( "GeV/c" );
 
   availiablePlots.insert( PlotPair( LeptonEta , PlotDef() ));
   availiablePlots[LeptonEta].setBinCount( 21 );
   availiablePlots[LeptonEta].setXMax(  2.1 );
   availiablePlots[LeptonEta].setXMin( -2.1 );
   availiablePlots[LeptonEta].setTitle( "Lepton #eta"   );
   availiablePlots[LeptonEta].setXtitle( "lepton #eta" );
   availiablePlots[LeptonEta].makeYtitle( "" );
 
   /*
   availiablePlots.insert( PlotPair( "VertexCountNoWeight" , PlotDef() ) );
   availiablePlots["VertexCountNoWeight"].setBinCount( 50 ); 
   availiablePlots["VertexCountNoWeight"].setXMax( 50 );
   availiablePlots["VertexCountNoWeight"].setXMin(  0 );
   availiablePlots["VertexCountNoWeight"].setTitle( "Num of Vertices (No weighting)" );
   availiablePlots["VertexCountNoWeight"].setXtitle( "Number of vertices" );
   availiablePlots["VertexCountNoWeight"].makeYtitle( "" );
   */

   availiablePlots.insert( PlotPair( VertexCount , PlotDef() ) );
   availiablePlots[VertexCount].setBinCount( 50 ); 
   availiablePlots[VertexCount].setXMax( 50 );
   availiablePlots[VertexCount].setXMin(  0 );
   availiablePlots[VertexCount].setTitle( "Num of Vertices" );
   availiablePlots[VertexCount].setXtitle( "Number of vertices" );
   availiablePlots[VertexCount].makeYtitle( "" );

   return true;
}


