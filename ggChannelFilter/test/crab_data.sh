#!/bin/bash

eval `scramv1 runtime -sh`
source /cvmfs/cms.cern.ch/crab3/crab.sh

if [[ ! -d config_files ]]; then 
   mkdir -p config_files
fi

for dataset in `cat Data_dataset.txt`; do
   echo $dataset
   name=${dataset%/*}
   name=${name#/}
   name=${name/\//_}
   echo $name 
   targetfile=config_files/${name}.py
   sed "s@DATASET@$dataset@" ./crab_template.py |
   sed "s@NAME@$name@" > $targetfile

   crab submit -c $targetfile
done
