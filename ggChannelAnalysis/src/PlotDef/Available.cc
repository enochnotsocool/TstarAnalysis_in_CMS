/*******************************************************************************
 *
 *  Filename    : Available.cc
 *  Description : Setting Available plots
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "PlotDef.h"

PlotList  availiableList;

bool initPlotList()
{
   availiableList.insert( PlotPair( "ChiSquareMass" , PlotDef() ));
   availiableList["ChiSquareMass"].setBinCount( 60 );
   availiableList["ChiSquareMass"].setXMax( 2000. );
   availiableList["ChiSquareMass"].setXMin( 100.  );
   availiableList["ChiSquareMass"].setTitle( "Mass of tg system"  );
   availiableList["ChiSquareMass"].setXtitle( "M_{tg} (GeV/c^{2})" );
   availiableList["ChiSquareMass"].setYtitle( "Events" );


   availiableList.insert( PlotPair( "JetPt" , PlotDef() ));
   availiableList["JetPt"].setBinCount( 60 );
   availiableList["JetPt"].setXMax( 600. );
   availiableList["JetPt"].setXMin( 0.   );
   availiableList["JetPt"].setTitle( "Jet p_{T}"   );
   availiableList["JetPt"].setXtitle( "jet p_{t}  (GeV/c)" );
   availiableList["JetPt"].setYtitle( "Jet Count" );
   
   availiableList.insert( PlotPair( "BJetPt" , PlotDef() ));
   availiableList["BJetPt"].setBinCount( 60 );
   availiableList["BJetPt"].setXMax( 600. );
   availiableList["BJetPt"].setXMin( 0.   );
   availiableList["BJetPt"].setTitle( "b-tagged Jet's p_{T}"   );
   availiableList["BJetPt"].setXtitle( "b jet p_{t}  (GeV/c)" );
   availiableList["BJetPt"].setYtitle( "b Jet Count" );
   
   availiableList.insert( PlotPair( "LeptonPt" , PlotDef() ));
   availiableList["LeptonPt"].setBinCount( 60 );
   availiableList["LeptonPt"].setXMax( 600. );
   availiableList["LeptonPt"].setXMin( 0.   );
   availiableList["LeptonPt"].setTitle( "Lepton p_{T}"   );
   availiableList["LeptonPt"].setXtitle( "lepton p_{t}  (GeV/c)" );
   availiableList["LeptonPt"].setYtitle( "lepton Count" );
   
   availiableList.insert( PlotPair( "JetCount" , PlotDef() ));
   availiableList["JetCount"].setBinCount( 6 );
   availiableList["JetCount"].setXMax( 11. );
   availiableList["JetCount"].setXMin( 5.   );
   availiableList["JetCount"].setTitle( "No. of Events with at Least N Jets" );
   availiableList["JetCount"].setXtitle( "At Least N Jets" );
   availiableList["JetCount"].setYtitle( "Events" );
   return true;
}
