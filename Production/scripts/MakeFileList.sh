#-------------------------------------------------------------------------------
#
#   File        : MakeFileList.sh
#   Descriptions: Create File list by das_client
#   Usage       : ./MakeFileList.sh [DataSet]
#
#-------------------------------------------------------------------------------
#!/bin/bash 

source $CMSSW_BASE/src/TstarAnalysis/Production/scripts/common.sh

for dataset in $( cat *.asc ); do 
   echo "Finding files under $dataset"
   sampleName=$( getDataSetName $dataset )
   rawList=$( das_client --limit=1000000 --query="file dataset=$dataset" | grep "store" )
   echo $rawList 
   echo $rawList  | grep "store" | sed "s@.root@.root\n@g"> ./FileList/${sampleName}.txt
done 


