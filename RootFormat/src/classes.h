#include "TstarAnalysis/RootFormat/interface/MiniEvent.h"
#include "TstarAnalysis/RootFormat/interface/MiniMuon.h"
#include "TstarAnalysis/RootFormat/interface/ChiSquareResult.h"
#include "TstarAnalysis/RootFormat/interface/HitFitResult.h"

namespace TstarAnalysis_RootFormat {
   struct dictionaryobjects {
      std::vector<MiniMuon>  v_mm;
      MiniMuon mm;
      MiniEvent me;
      ChiSquareResult csr;
      HitFitResult    hfr;
   }; 
}
