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

   availiableList.insert( PlotPair( "MET" , PlotDef() ));
   availiableList["MET"].setBinCount( 60 );
   availiableList["MET"].setXMax( 600. );
   availiableList["MET"].setXMin( 0. );
   availiableList["MET"].setTitle( "Missing Transverse Energy" );
   availiableList["MET"].setXtitle( "M_{E_{T}} (GeV)");
   availiableList["MET"].setYtitle( "Events" );

   availiableList.insert( PlotPair( "JetPt" , PlotDef() ));
   availiableList["JetPt"].setBinCount( 60 );
   availiableList["JetPt"].setXMax( 600. );
   availiableList["JetPt"].setXMin( 0.   );
   availiableList["JetPt"].setTitle( "Jet p_{T}"   );
   availiableList["JetPt"].setXtitle( "Jet p_{t}  (GeV/c)" );
   availiableList["JetPt"].setYtitle( "Jet Count" );
   
   availiableList.insert( PlotPair( "JetEta" , PlotDef() ));
   availiableList["JetEta"].setBinCount(60);
   availiableList["JetEta"].setXMin(-2.4);
   availiableList["JetEta"].setXMax( 2.4);
   availiableList["JetEta"].setTitle( "Jet #eta");
   availiableList["JetEta"].setXtitle("Jet #eta");
   availiableList["JetEta"].setYtitle("Jet Count");
   
   availiableList.insert( PlotPair( "JetCount" , PlotDef() ));
   availiableList["JetCount"].setBinCount( 10 );
   availiableList["JetCount"].setXMax( 15. );
   availiableList["JetCount"].setXMin( 5.   );
   availiableList["JetCount"].setTitle( "No. of Events with N Jets" );
   availiableList["JetCount"].setXtitle( "No. of Jets" );
   availiableList["JetCount"].setYtitle( "Events" );
   
   availiableList.insert( PlotPair( "LeptonPt" , PlotDef() ));
   availiableList["LeptonPt"].setBinCount( 60 );
   availiableList["LeptonPt"].setXMax( 600. );
   availiableList["LeptonPt"].setXMin( 0.   );
   availiableList["LeptonPt"].setTitle( "Lepton p_{T}"   );
   availiableList["LeptonPt"].setXtitle( "lepton p_{t}  (GeV/c)" );
   availiableList["LeptonPt"].setYtitle( "lepton Count" );
 
   availiableList.insert( PlotPair( "LeptonEta" , PlotDef() ));
   availiableList["LeptonEta"].setBinCount( 60 );
   availiableList["LeptonEta"].setXMax(  2.1 );
   availiableList["LeptonEta"].setXMin( -2.1 );
   availiableList["LeptonEta"].setTitle( "Lepton #eta"   );
   availiableList["LeptonEta"].setXtitle( "lepton #eta" );
   availiableList["LeptonEta"].setYtitle( "lepton Count" );
   
   return true;
}
