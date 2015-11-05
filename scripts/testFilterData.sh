#-------------------------------------------------------------------------------
#
#   File        : testFilterData.sh
#   Descriptions: Short script for testing filter against data
#   Usage       : ./testFilterData.sh Option
#
#-------------------------------------------------------------------------------
#!/bin/bash 

cmsRun runFilter.py \
   sample=file:/wk_cms/yichen/miniAODs/Run2015D_PromptReco-v4/SingleMuon.root  \
   DataProcessing=Data25ns \
   maxEvts=10000
