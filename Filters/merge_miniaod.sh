#-------------------------------------------------------------------------------
#
#   File        : merge_miniaod.sh
#   Descriptions: Merging all miniAODS 
#   Usage       : ./merge_miniaod.sh
#
#-------------------------------------------------------------------------------
#!/bin/bash

source $CMSSW_BASE/src/TstarAnalysis/scripts/MergeInDirectory.sh

MINIAOD_BASE=./data/MINIAODS
STORE_BASE=/wk_cms/$USER/TstarAnalysis/

for channel in $(ls $MINIAOD_BASE ); do
   outputdir=$STORE_BASE/${channel}_MiniAODs/
   for sample in $(ls $MINIAOD_BASE/$channel ); do
      output_filename=${sample}
      output_filename=${output_filename%%_Tune*}
      output_filename=${output_filename%%_4f*}
      output_filename=${output_filename%%_5f*}
      output_filename=${output_filename}.root

      outputpath=${outputdir}/${output_filename}
      inputpath=${MINIAOD_BASE}/${channel}/${sample}

      while true; do
         num_of_merge=$( ps -U ${USER} | grep cmsRun | wc --lines )
         num_of_thread=$(cat /proc/cpuinfo | grep processor | wc --lines )
         num_of_thread=$((num_of_thread/2))
         if [[ $num_of_merge -lt $num_of_thread ]]; then
            echo Running for ${outputpath}
            MergeInDirectory $outputpath $inputpath &> /dev/null &
            break 
         else
            printf "\rToo Many instances running! ${num_of_merge}/${num_of_thread} ($(date))";
            sleep 5; 
         fi 
      done
   done
done

while true; do
   num_of_merge=$( ps -U ${USER} | grep cmsRun | wc --lines )
   if [[ $num_of_merge == "0" ]]; then
      echo "All Done!"
      break;
   fi

   printf "\rStill $num_of_merge instances running... ($(date))"
   sleep 20
done
