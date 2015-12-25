/*******************************************************************************
 *
 *  Filename    : Stringify.cc
 *  Description : String return for enum value for Root object creation
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/PlotDef.h"
#include "TstarAnalysis/CombineAnalysis/interface/SampleMgr.h"

using namespace std;

std::string Stringify( const PlotName x )
{
   if( x == ChiSquareTstarMass ) { return "t+g inveriant Mass (#chi^{2} Method)"; }
   if( x == ChiSquareTMass ) { return "t Mass (#chi^{2} Method)"; }

   if( x == HitFitTstarMass ) { return "t+g invariant mass (HitFit Package)"; }
   if( x == HitFitTMass) { return "t Mass (HitFit Pacakge)"; }

   if( x == JetPt        ) { return "JetPt"; }
   if( x == JetEta       ) { return "JetEta"; }
   if( x == JetCount     ) { return "JetCount"; }
   if( x == LeptonPt     ) { return "LeptonPt"; }
   if( x == LeptonEta    ) { return "LeptonEta"; }
   if( x == MET          ) { return "MET"; }
   if( x == VertexCount  ) { return "VertexCount"; } 
   return "";
}

PlotName PlotNameFromString( const string& x )
{
   if( x == "ChiSquareTstarMass" ) { return ChiSquareTstarMass; }
   if( x == "ChiSquareTMass"     ) { return ChiSquareTMass   ; } 
   if( x == "HitFitTstarMass"    ) { return HitFitTstarMass  ; } 
   if( x == "HitFitTMass"        ) { return HitFitTMass      ; } 
   if( x == "JetPt"              ) { return JetPt            ; } 
   if( x == "JetEta"             ) { return JetEta           ; } 
   if( x == "JetCount"           ) { return JetCount         ; } 
   if( x == "LeptonPt"           ) { return LeptonPt         ; } 
   if( x == "LeptonEta"          ) { return LeptonEta        ; } 
   if( x == "MET"                ) { return MET              ; } 
   if( x == "VertexCount"        ) { return VertexCount      ; }
   return PLOTNAME_END;

}

std::string Stringify( const SampleName x) 
{
   if( x == TTW_Lepton    ) { return "TTW_Lepton"; } 
   if( x == TTW_Quark     ) { return "TTW_Quark"; } 
   if( x == TTZ_Lepton    ) { return "TTZ_Lepton"; } 
   if( x == TTZ_Quark     ) { return "TTZ_Quark"; } 
   if( x == WJets         ) { return "WJets"; } 
   if( x == ZJets         ) { return "ZJets"; } 
   if( x == WW            ) { return "WW"; } 
   if( x == WZ            ) { return "WZ"; } 
   if( x == ZZ            ) { return "ZZ"; } 
   if( x == SingleT_S     ) { return "SingleT_S"; } 
   if( x == SingleT_T     ) { return "SingleT_T"; } 
   if( x == SingleT_TW    ) { return "SingleT_TW"; } 
   if( x == SingleTbar_TW ) { return "SingleTbar_TW"; }
   if( x == TTJets        ) { return "TTJets"; } 
   if( x == Tstar_M0700   ) { return "Tstar_M0700"; } 
   if( x == Tstar_M0800   ) { return "Tstar_M0800"; } 
   if( x == Tstar_M0900   ) { return "Tstar_M0900"; } 
   if( x == Tstar_M1000   ) { return "Tstar_M1000"; } 
   if( x == Tstar_M1100   ) { return "Tstar_M1100"; } 
   if( x == Tstar_M1200   ) { return "Tstar_M1200"; } 
   if( x == Tstar_M1300   ) { return "Tstar_M1300"; } 
   if( x == Tstar_M1400   ) { return "Tstar_M1400"; } 
   if( x == Tstar_M1500   ) { return "Tstar_M1500"; } 
   if( x == Tstar_M1600   ) { return "Tstar_M1600"; } 
   if( x == Data          ) { return "Data"; } 

   return "";
}

SampleName SampleFromString( const std::string& input )
{
   if( input ==  "TTW_Lepton"   ) { return  TTW_Lepton     ; } 
   if( input ==  "TTW_Quark"    ) { return  TTW_Quark      ; } 
   if( input ==  "TTZ_Lepton"   ) { return  TTZ_Lepton     ; } 
   if( input ==  "TTZ_Quark"    ) { return  TTZ_Quark      ; } 
   if( input ==  "WJets"        ) { return  WJets          ; } 
   if( input ==  "ZJets"        ) { return  ZJets          ; } 
   if( input ==  "WW"           ) { return  WW             ; } 
   if( input ==  "WZ"           ) { return  WZ             ; } 
   if( input ==  "ZZ"           ) { return  ZZ             ; } 
   if( input ==  "SingleT_S"    ) { return  SingleT_S      ; } 
   if( input ==  "SingleT_T"    ) { return  SingleT_T      ; } 
   if( input ==  "SingleT_TW"   ) { return  SingleT_TW     ; } 
   if( input ==  "SingleTbar_TW") { return  SingleTbar_TW  ; } 
   if( input ==  "TTJets"       ) { return  TTJets         ; } 
   if( input ==  "Tstar_M0700"  ) { return  Tstar_M0700    ; } 
   if( input ==  "Tstar_M0800"  ) { return  Tstar_M0800    ; } 
   if( input ==  "Tstar_M0900"  ) { return  Tstar_M0900    ; } 
   if( input ==  "Tstar_M1000"  ) { return  Tstar_M1000    ; } 
   if( input ==  "Tstar_M1100"  ) { return  Tstar_M1100    ; } 
   if( input ==  "Tstar_M1200"  ) { return  Tstar_M1200    ; } 
   if( input ==  "Tstar_M1300"  ) { return  Tstar_M1300    ; } 
   if( input ==  "Tstar_M1400"  ) { return  Tstar_M1400    ; } 
   if( input ==  "Tstar_M1500"  ) { return  Tstar_M1500    ; } 
   if( input ==  "Tstar_M1600"  ) { return  Tstar_M1600    ; } 
   if( input ==  "Data"         ) { return  Data           ; } 
   return DUMMY_END;
}


