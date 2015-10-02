#!/bin/bash

REMOTE_SERVER="ntugrid4.phys.ntu.edu.tw"
REMOTE_BASE="/cms/store/user/yichen/"
LOCAL_DIR="./"
TARGET=""

function main() {
   parseInput $@
   dataSetDirList=$(descendxrd ${REMOTE_BASE}${TARGET} 1)
   for dataSetDir in $dataSetDirList; do
      dataSet=${dataSetDir##/*/}
      echo $dataSet
      datasetDir=${LOCAL_DIR}/${TARGET}/${dataSet}
      mkdir -p $datasetDir

      datasetFileList=$(descendxrd ${REMOTE_BASE}/${TARGET}/${dataSet} 4 )
      for file in $datasetFileList ; do
         if [[ $file = *.root ]]; then
            echo "Copying $file ..."
            xrdcp root://$REMOTE_SERVER//$file $datasetDir 
         fi
      done
   done
}

function descendxrd() {
   local presentPath=$1
   local level=$2
   if [[ $level == 0 ]]; then
      echo $presentPath
   else
      nextPathList=$( xrdfs $REMOTE_SERVER ls $presentPath )
      for nextPath in $nextPathList ; do
         descendxrd $nextPath $((level-1))
      done
   fi
}

function parseInput() {
   for arg in $@ ; do
      if [[ "$arg" == Target=* ]]; then
         TARGET=${arg#Target=*}
      elif [[ $arg == remoteServer=* ]]; then
         REMOTE_SERVER=${arg#remoteServer=}
      elif [[ $arg == remote_base=* ]]; then
         REMOTE_BASE=${arg#remoteBase=}
      elif [[ $arg == localDir=* ]]; then
         LOCAL_DIR=${arg#localDir=}
      else
         echo "Warning: skipping over unknown argument $arg"
      fi
   done;

   if [[ $TARGET == "" ]]; then
      echo "Error: No Target input!"
      exit -1 
   fi
   echo "Getting target $TARGET from root://$REMOTE_SERVER:/$REMOTE_BASE"
}

main $@
