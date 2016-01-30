#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include <boost/python.hpp>

using namespace boost::python;
 
BOOST_PYTHON_MODULE(pluginCombineMgr)
{
   class_<CombineMgr>("CombineMgr")
      .def("InitPlots"           , &CombineMgr::InitPlots           )
      .def("InitSamples"         , &CombineMgr::InitPlots           )
      .def("InitChannels"        , &CombineMgr::InitChannels        )
      .def("SetChannelFile"      , &CombineMgr::SetChannelFile      )
      .def("SetChannelColors"    , &CombineMgr::SetChannelColors    )
      .def("SetChannelWeights"   , &CombineMgr::SetChannelWeights   )
      .def("SetChannelSelection" , &CombineMgr::SetChannelSelection )
      .def("AvailablePlots"      , &CombineMgr::AvailablePlots      )
      .def("AvailableSamples"    , &CombineMgr::AvailableSamples    )
      .def("AvailableChannels"   , &CombineMgr::AvailableChannels   )

      ;
};

