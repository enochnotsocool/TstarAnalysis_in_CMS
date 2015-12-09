#-------------------------------------------------------------------------------
#
#   File        : RunAll.sh
#   Descriptions: Run all samples 
#   Usage       : ./RunAll.sh
#
#-------------------------------------------------------------------------------
#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

FILTER_TYPE="gg_MuonSignal"
MuonData=""

for filter in ${FILTER_TYPE} ; do 
   for MCSample in $( cat MCSetList.asc ) ; do
      ${DIR}/RunSample.sh $filter $MCSample
   done

   for DataSample in $( cat DataSetList.asc ); do 
      if [[ $filter == *"Muon"* ]]  ; then
         if [[ $DataSample == *"Muon"* ]]; then
            ${DIR}/RunSample.sh $filter $DataSample
         fi
      elif [[ $filter == *"Electron"* ]] ; then
         if [[ $DataSample == *"Electron"* ]]; then
            ${DIR}/RunSample.sh $filter $DataSample 
         fi
      fi
   done
done

