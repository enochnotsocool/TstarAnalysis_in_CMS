#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include <boost/python.hpp>

using namespace boost::python;
 
BOOST_PYTHON_MODULE(pluginCombineMgr)
{
   class_<CombineMgr>("CombineMgr")
      .def("InitPlots"           , &CombineMgr::InitPlots           )
      .def("InitSamples"         , &CombineMgr::InitSamples         )
      .def("InitChannels"        , &CombineMgr::InitChannels        )
      .def("SetChannelFile"      , &CombineMgr::SetChannelFile      )
      .def("SetChannelColors"    , &CombineMgr::SetChannelColors    )
      .def("SetChannelWeights"   , &CombineMgr::SetChannelWeights   )
      .def("SetChannelSelection" , &CombineMgr::SetChannelSelection )
      .def("MakeBasicPlots"      , &CombineMgr::MakeBasicPlots      )
      .def("MakeDataBGPlot"      , &CombineMgr::MakeDataBGPlot      )
      .def("HC_MakeRequirements" , &CombineMgr::HC_MakeRequirements )
      .def("HC_RunCombine"       , &CombineMgr::HC_RunCombine       )
      .def("HC_PlotLimit"        , &CombineMgr::HC_PlotLimit        )
      .def("AvailablePlots"      , &CombineMgr::AvailablePlots      )
      .def("AvailableSamples"    , &CombineMgr::AvailableSamples    )
      .def("AvailableChannels"   , &CombineMgr::AvailableChannels   )

      ;
};

