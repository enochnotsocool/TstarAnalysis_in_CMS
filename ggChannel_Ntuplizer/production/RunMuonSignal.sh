#-------------------------------------------------------------------------------
#
#   File        : RunSamples.sh
#   Descriptions: Running over filtered miniAOD samples
#   Usage       : ./RunSamples.sh
#
#-------------------------------------------------------------------------------
#!/bin/bash

InputDir="/wk_cms/yichen/TstarAnalysis/gg_MuonSignal_MiniAODs/"
TargetDir="/wk_cms/yichen/TstarAnalysis/gg_MuonSignal_ntuples/"

for file in $(ls $InputDir) ; do 
   DataProcessing=""
   if [[ $file == *"Run2015D-PromptReco"* ]]; then
      DataProcessing="Data25ns_PromptRecov4"
   elif [[ $file == *"Run2015D"* ]]; then
      DataProcessing="Data25ns_ReReco"
   elif [[ $file == *"Run2015C"* ]]; then
      DataProcessing="Data25ns_ReReco"
   else
      DataProcessing="MC25ns_MiniAODv2"
   fi

   outputfile=${file%%.root}_Ntuple.root
   echo $outputfile 

   logfile=log_MuonSignal_${outputfile%.root}.txt
   cmsRun ggChannel_Ntuplizer_cfg.py       \
      maxEvents=-1                         \
      sample="file:///${InputDir}/$file"   \
      outputLabel="$TargetDir/$outputfile" \
      DataProcessing=$DataProcessing &> $logfile &
done
