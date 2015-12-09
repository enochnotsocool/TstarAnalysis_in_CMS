#-------------------------------------------------------------------------------
#
#   File        : RunSample.sh
#   Descriptions: Running designated filter on single sample
#   Usage       : ./RunSample.sh [filter type] [sample]
#
#-------------------------------------------------------------------------------
#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
PYTHON_DIR=$DIR/PYTHONFILES
SCRIPT_DIR=$DIR/RUNSCRIPTS
OUTPUT_DIR=$DIR/LOG
MINIAOD_DIR=$DIR/MINIAODS
HISTOGRAM_DIR=$DIR/HISTOGRAMS
SPLIT_PREFIX=$DIR/.files_

function main() 
{
   parseArguments $@
   filterType=$1
   sample=$2 
   
   name=$( makeName $sample )
   makeDirectories $filterType $name
   
   makefileLists $sample
   for file in $( ls ${SPLIT_PREFIX}* ) ; do
      label=${file/${SPLIT_PREFIX}/}

      DataProcessing=$( getDataProcess $sample )
      jsonFile=$( getJson $sample )
      pythonFile=${PYTHON_DIR}/${filterType}/${name}/cfg_${label}.py
      scriptFile=${SCRIPT_DIR}/${filterType}/${name}/run_${label}.sh
      logFile=${OUTPUT_DIR}/${filterType}/${name}/log_${label}.txt
      histFile=${HISTOGRAM_DIR}/${filterType}/${name}/hist_${label}.root
      miniAODFile=${MINIAOD_DIR}/${filterType}/${name}/MiniAOD_${label}.root

      fileListArray=( $( cat $file ) )
      sampleList=""
      for item in ${fileListArray[@]} ; do 
         sampleList=${sampleList}"\"${item}\","
      done

      ## Making python file 
      cat $DIR/runfilter_template.py                   |
      sed -e "s@__DATAPROCESSING__@${DataProcessing}@" | 
      sed -e "s@__SAMPLES__@${sampleList}@"            |
      sed -e "s@__JSONFILE__@${jsonFile}@"             |
      sed -e "s@__OUTPUT_LABEL__@${miniAODFile}@"      |
      sed -e "s@__HIST_FILE__@${histFile}@"            |
      sed -e "s@__FILTER_TYPE__@${filterType}@"        |
      cat > $pythonFile

      ## Making script file 
      echo "#!/bin/bash"   >  $scriptFile
      echo "cd $DIR/../../../"                >> $scriptFile
      echo "eval \`scramv1 runtime -sh\`"     >> $scriptFile
      echo "cmsRun $pythonFile &> ${logFile}" >> $scriptFile
      chmod +x $scriptFile

      echo "Running on sample $name - $label"
      rm $file 
   done
}

function makeName()
{
   echo $1 | awk -F "/" '{print $2"_"$3 }' 
}
function getDataProcess() 
{
   local data_set=$1
   if [[ $data_set == *"RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1"* ]]; then
      echo "MC25ns_MiniAODv2"
   elif [[ $data_set == *"RunIISpring15MiniAODv2-Asympt50ns_74X_mcRun2_asymptotic50ns_v0-v1"* ]]; then
      echo "MC50ns_MiniAODv2"
   elif [[ $data_set == *"Run2015D-PromptReco-v4"* ]]; then
      echo "Data25ns_PromptRecov4"
   elif [[ $data_set == *"Run2015D-05Oct2015"* ]]; then
      echo "Data25ns_MiniAODv2"
   elif [[ $data_set == *"Run2015C_25ns-05Oct2015"* ]]; then
      echo "Data25ns_ReReco"
   elif [[ $data_set == *"Run2015"*"05Oct2015"* ]]; then
      echo "Data50ns_MiniAODv2"
   elif [[ $data_set == *"RunIISpring15DR74"* ]]; then
      echo "MC25ns_MiniAODv1"
   else
      echo ""
   fi
}

function makeDirectories()
{
   filterType=$1
   name=$2
   mkdir -p  ${PYTHON_DIR}/${filterType}/${name}
   mkdir -p  ${SCRIPT_DIR}/${filterType}/${name}
   mkdir -p  ${OUTPUT_DIR}/${filterType}/${name}
   mkdir -p  ${HISTOGRAM_DIR}/${filterType}/${name}
   mkdir -p  ${MINIAOD_DIR}/${filterType}/${name}
}

function makefileLists()
{
   sample=$1
   das_client --limit=1000000 --query="file dataset=$sample" | grep "store" > .temp.txt
   split -l 16 .temp.txt $SPLIT_PREFIX 
   rm .temp.txt
}

function parseArguments()
{
   filterType=$1 
   if [[ $filterType == "gg_MuonSignal" ]]; then
      echo "Running gg Channel Muon Signal Region"
   else
      echo "Error! Unrecognised filter type!"
      exit 1
   fi
}

function getJson()
{
   if [[ $1 == *"Run2015"* ]]; then
      echo "$DIR/Cert_25ns_Latest.json" 
   else 
      echo ""
   fi
}

main $@
