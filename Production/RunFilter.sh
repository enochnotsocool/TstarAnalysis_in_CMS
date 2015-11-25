#-------------------------------------------------------------------------------
#
#   File        : RunFilter.sh
#   Descriptions: Script for running sample filter over all datasets 
#   Usage       : ./RunFilter.sh [ gg_MuonSignal | gg_ElectronSignal ] 
#
#-------------------------------------------------------------------------------

source $CMSSW_BASE/src/TstarAnalysis/Production/scripts/common.sh

channel=""
Config_Dir=""
Tuple_Dir=""
Hist_Dir=""
Log_Dir=""
datasetList=""

function main(){
   parseArguments $@
   makeRequirements $@

   for dataset in $datasetList ; do 
      echo "Working on dataset $dataset:"
      local Name=$( getDataSetName $dataset )
      local DataProcess=$( getDataProcess $dataset )
      local jsonFile=$( getJsonFile $dataset )

      echo ">>> Name:        $Name"
      echo ">>> DataProcess: $DataProcess"
      echo ">>> JsonFile:    $jsonFile"

      echo ">>> Getting files for data set.... "
      das_client --limit=10000000 --query "file dataset=$dataset" | 
         grep "store" > ./temp.txt

      echo ">>> Query Results"
      cat ./temp.txt

      echo ">>> Splitting query results"
      local shell_files="$Config_Dir/$Name/file_"
      rm ${shell_files}*
      split -l 16 ./temp.txt $shell_files
      echo ">>> Finished splitting files..."

      #-----  Parsing files  ---------------------------------------------------------
      for file in $(ls "$shell_files"*) ; do
         cmd=$( makeCMD $Name $file )

         echo "#!/bin/bash" > temp.txt
         echo "cd $(pwd)"   >> temp.txt 
         echo "eval \`scramv1 runtime -sh\`" >> temp.txt 
         echo $cmd >> temp.txt
         mv temp.txt $file

         mv $file ${file}.sh
         chmod +x ${file}.sh
         # bsub -q 2nd ${file}.sh
      done

      echo -e "\n\n"
   done
}

function makeCMD()
{
   name=$1
   file=$2
   file_name=${file##*/}
   sampleList=""
   for sample in $(cat $file) ; do
      sampleList=$sampleList","$sample
   done
   sampleList=${sampleList#,}

   if [[ $channel == "gg_MuonSignal" || $channel == "gg_ElectronSignal" ]]; then
      output_tuple_file=$Tuple_Dir/$Name/Tuple_${file_name}.root
      output_hist_file=$Hist_Dir/$Name/Hist_${file_name}.root
      output_log_file=$Log_Dir/$Name/log_${file_name}.txt

      cmd="cmsRun $(pwd)/python/RunFilter.py"
      cmd=${cmd}" DataProcessing=$DataProcess"
      cmd=${cmd}" outputLabel=$output_tuple_file"
      cmd=${cmd}" histFile=$output_hist_file"
      cmd=${cmd}" maxEvents=-1"
      cmd=${cmd}" jsonFile=$jsonFile"
      cmd=${cmd}" sample=$sampleList"
      cmd=${cmd}" filterType=$channel"
      cmd=${cmd}" &> $output_log_file"
   fi
   echo $cmd
}

function parseArguments()
{
   if [[ $# != 1 ]]; then
      echo "Error! Requires exactly 1 argument!"
      exit -1
   fi

   if [[ $1 == "gg_MuonSignal" ]] ; then 
      channel=$1
   elif [[ $1 == "gg_ElectronSignal" ]]; then
      channel=$1
   else
      echo "Error! Unrecognized argument $1!"
      exit -1
   fi

   echo "Running $channel Filter..."
}

function makeRequirements()
{
   Config_Dir=$(pwd)"/Config/$channel"
   Tuple_Dir=$(pwd)"/FilteredMiniAOD//$channel"
   Hist_Dir=$(pwd)"/Histograms/$channel"
   Log_Dir=$(pwd)"/OutputLog/$channel"
   datasetList=$( cat ./MCSetList.asc )

   for dataset in $datasetList ; do 
      local name=$(getDataSetName $dataset )
      mkdir -p $Config_Dir/$name
      mkdir -p $Tuple_Dir/$name
      mkdir -p $Hist_Dir/$name
      mkdir -p $Log_Dir/$name
   done
   
   echo "Finish making requirements..."
}


main $@
