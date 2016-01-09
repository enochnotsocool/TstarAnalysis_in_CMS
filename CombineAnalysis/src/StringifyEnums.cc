/*******************************************************************************
 *
 *  Filename    : Stringify.cc
 *  Description : String return for enum value for Root object creation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/Enums.h"
using namespace std;

#define STRING_TO_ENUM( X , Y )\
   if( X == #Y ) { return Y; }

#define ENUM_TO_STRING( X , Y )\
   if( X == Y ) { return #Y ; }

//------------------------------------------------------------------------------ 
//   Plot Functions
//------------------------------------------------------------------------------
string Stringify( const PlotName x )
{
   
   ENUM_TO_STRING( x , JetPt              );
   ENUM_TO_STRING( x , JetEta             );
   ENUM_TO_STRING( x , JetCount           );
   ENUM_TO_STRING( x , LeptonPt           );
   ENUM_TO_STRING( x , LeptonEta          );
   ENUM_TO_STRING( x , MET                );
   ENUM_TO_STRING( x , VertexCount        );
   ENUM_TO_STRING( x , ChiSquareTstarMass );
   ENUM_TO_STRING( x , ChiSquareTMass     );
   ENUM_TO_STRING( x , HitFitTstarMass    );
   ENUM_TO_STRING( x , HitFitTMass        );
   return "";
}

PlotName PlotNameFromString( const string& x )
{
   STRING_TO_ENUM( x , ChiSquareTstarMass );
   STRING_TO_ENUM( x , ChiSquareTMass     );
   STRING_TO_ENUM( x , HitFitTstarMass    );
   STRING_TO_ENUM( x , HitFitTMass        );
   STRING_TO_ENUM( x , JetPt              );
   STRING_TO_ENUM( x , JetEta             );
   STRING_TO_ENUM( x , JetCount           );
   STRING_TO_ENUM( x , LeptonPt           );
   STRING_TO_ENUM( x , LeptonEta          );
   STRING_TO_ENUM( x , MET                );
   STRING_TO_ENUM( x , VertexCount        );
   return PLOTNAME_END;
}

//------------------------------------------------------------------------------ 
//   Sample Functions
//------------------------------------------------------------------------------
std::string Stringify( const SampleName x) 
{
   ENUM_TO_STRING( x , TTW_Lepton    );
   ENUM_TO_STRING( x , TTW_Quark     );
   ENUM_TO_STRING( x , TTZ_Lepton    );
   ENUM_TO_STRING( x , TTZ_Quark     );
   ENUM_TO_STRING( x , TT_PLUS_BOSON );

   ENUM_TO_STRING( x , WJets         );
   ENUM_TO_STRING( x , ZJets         );
   ENUM_TO_STRING( x , WW            );
   ENUM_TO_STRING( x , WZ            );
   ENUM_TO_STRING( x , ZZ            );
   ENUM_TO_STRING( x , BOSONS        );

   ENUM_TO_STRING( x , SingleT_S     );
   ENUM_TO_STRING( x , SingleT_T     );
   ENUM_TO_STRING( x , SingleT_TW    );
   ENUM_TO_STRING( x , SingleTbar_TW );
   ENUM_TO_STRING( x , SINGLE_T      );

   ENUM_TO_STRING( x , TTJets        );
   
   ENUM_TO_STRING( x , Tstar_M0700   );
   ENUM_TO_STRING( x , Tstar_M0800   );
   ENUM_TO_STRING( x , Tstar_M0900   );
   ENUM_TO_STRING( x , Tstar_M1000   );
   ENUM_TO_STRING( x , Tstar_M1100   );
   ENUM_TO_STRING( x , Tstar_M1200   );
   ENUM_TO_STRING( x , Tstar_M1300   );
   ENUM_TO_STRING( x , Tstar_M1400   );
   ENUM_TO_STRING( x , Tstar_M1500   );
   ENUM_TO_STRING( x , Tstar_M1600   );
   
   ENUM_TO_STRING( x , Data          );

   return "";
}

SampleName SampleFromString( const std::string& input )
{
   STRING_TO_ENUM( input , TTW_Lepton    ) ; 
   STRING_TO_ENUM( input , TTW_Quark     ) ; 
   STRING_TO_ENUM( input , TTZ_Lepton    ) ; 
   STRING_TO_ENUM( input , TTZ_Quark     ) ;
   STRING_TO_ENUM( input , TT_PLUS_BOSON ) ;

   STRING_TO_ENUM( input , WJets         ) ; 
   STRING_TO_ENUM( input , ZJets         ) ; 
   STRING_TO_ENUM( input , WW            ) ; 
   STRING_TO_ENUM( input , WZ            ) ; 
   STRING_TO_ENUM( input , ZZ            ) ; 
   STRING_TO_ENUM( input , BOSONS        ) ;

   STRING_TO_ENUM( input , SingleT_S     ) ; 
   STRING_TO_ENUM( input , SingleT_T     ) ; 
   STRING_TO_ENUM( input , SingleT_TW    ) ; 
   STRING_TO_ENUM( input , SingleTbar_TW ) ; 
   STRING_TO_ENUM( input , SINGLE_T      ) ;

   STRING_TO_ENUM( input , TTJets        ) ; 

   STRING_TO_ENUM( input , Tstar_M0700   ) ; 
   STRING_TO_ENUM( input , Tstar_M0800   ) ; 
   STRING_TO_ENUM( input , Tstar_M0900   ) ; 
   STRING_TO_ENUM( input , Tstar_M1000   ) ; 
   STRING_TO_ENUM( input , Tstar_M1100   ) ; 
   STRING_TO_ENUM( input , Tstar_M1200   ) ; 
   STRING_TO_ENUM( input , Tstar_M1300   ) ; 
   STRING_TO_ENUM( input , Tstar_M1400   ) ; 
   STRING_TO_ENUM( input , Tstar_M1500   ) ; 
   STRING_TO_ENUM( input , Tstar_M1600   ) ; 
   STRING_TO_ENUM( input , Data          ) ; 
   return DUMMY_END;
}

//------------------------------------------------------------------------------ 
//   Channel functions
//------------------------------------------------------------------------------
string Stringify( const ChannelName input )
{
   if( input == ggMuon ) { return "ggMuon"; }
   return "";
}

ChannelName ChannelFromString( const string& input )
{
   if( input == "ggMuon" ) { return ggMuon; }
   return CHANNEL_END;
}

