#-------------------------------------------------------------------------------
#
#   File        : RunSample.sh
#   Descriptions: Run the ggChannel filter over a designated data set
#   Usage       : ./RunSample.sh [Dataset] ## Exactly one argument
#
#-------------------------------------------------------------------------------
#!/bin/bash

Config_Dir=$(pwd)"/Config"
Tuple_Dir=$(pwd)"/Tuples"
Hist_Dir=$(pwd)"/Histograms"

function main(){
   parseArguments $@
   local dataset=$1
   local Name=$( getDataSetName $dataset )
   local DataProcess=$( getDataProcess $dataset )
   local jsonFile=$( getJsonFile $dataset )
   mkdir -p $Config_Dir/$Name
   mkdir -p $Tuple_Dir/$Name
   mkdir -p $Hist_Dir/$Name

   echo "Finished Parsing arguments...."

   das_client --limit=100000 --query="file dataset=$dataset"  | grep "store" > temp.txt
   if [[ ! -s temp.txt ]]; then
      echo "Error! No miniAOD files found for $dataset"
      exit -1
   fi
   local shell_files="$Config_Dir/$Name/file_"
   rm ${shell_files}*
   split -l 32 temp.txt $shell_files
   echo "Finished splitting files..."
   #-----  Parsing files  ---------------------------------------------------------
   for file in $(ls "$shell_files"*) ; do
      echo $file
      file_name=${file##*/}
      output_tuple_file=$Tuple_Dir/$Name/Tuple_${file_name}.root
      output_hist_file=$Hist_Dir/$Name/Hist_${file_name}.root
      cmd="cmsRun $(pwd)/makeTuples_cfg.py"
      cmd=${cmd}" DataProcessing=$DataProcess"
      cmd=${cmd}" outputLabel=$output_tuple_file"
      cmd=${cmd}" histFile=$output_hist_file"
      cmd=${cmd}" maxEvts=10"
      cmd=${cmd}" jsonFile=$jsonFile"
      cmd=${cmd}" sample="
      cat $file  |
         sed 's@root@root,\\@' |
         sed '$s/\,\\//g'      |
         sed "1i${cmd}"        |
         sed 's@sample=@sample=\\@'|
         sed '1ieval \`scramv1 runtime -sh\`' |
         sed "1icd $(pwd)" |
         sed "1i#!/bin/bash" > temp.txt
      mv temp.txt $file
      mv $file ${file}.sh
      chmod +x ${file}.sh
      #bsub -q 1nd $file
   done
}



function getDataSetName(){
   local dataset=$1
   echo $dataset | awk -F "/" '{print $2"_"$3 }'  
}

function parseArguments(){
   if [[ $# != 1 ]]; then
      echo "Error! Takes exactly on argument!"
      exit -1
   fi
}

function getDataProcess(){
   if [[ $1 == *"Run2015"* ]]; then
      echo "Data25ns"
   else
      echo "MC25ns"
   fi
}

function getJsonFile(){
   if [[ $1 == *"Run2015"* ]]; then
      echo "$(pwd)/jsonFile.txt" 
   else 
      echo ""
   fi
}

main $@
