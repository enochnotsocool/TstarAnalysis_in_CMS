#-------------------------------------------------------------------------------
#
#   File        : testFilterMC.sh
#   Descriptions: Short script for testing filter against data
#   Usage       : ./testFilterMC.sh Option
#
#-------------------------------------------------------------------------------
#!/bin/bash 

cmsRun runFilter.py \
   sample=file:/wk_cms/yichen/miniAODs/MC_reMiniAOD_25ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root \
   DataProcessing=MC25ns \
   maxEvts=10000
