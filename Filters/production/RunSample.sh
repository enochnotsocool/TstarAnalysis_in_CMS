#-------------------------------------------------------------------------------
#
#   File        : RunSample.sh
#   Descriptions: Running designated filter on single sample
#   Usage       : ./RunSample.sh [filter type] [sample]
#
#-------------------------------------------------------------------------------
#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
source ${DIR}/source/DataSetParser.sh

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
   split -l 4 .temp.txt $SPLIT_PREFIX 
   rm .temp.txt
}

function parseArguments()
{
   filterType=$1 
   if [[ $filterType == "gg_MuonSignal" ]]; then
      echo "Running gluon-gluon Channel Muon Signal Region"
   elif [[ $filterType == "gg_ElectronSignal" ]]; then
      echo "Running gluon-gluon Channel Electron Signal Region"
   else
      echo "Error! Unrecognised filter type!"
      exit 1
   fi
}

main $@
