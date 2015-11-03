#-------------------------------------------------------------------------------
#
#   File        : getEfficiency.sh
#   Descriptions: Simple script for getting total efficiency from directory
#   Usage       : ./getEfficiency.sh
#
#-------------------------------------------------------------------------------
#!/bin/bash

for dir in * ; do 
   if [[ ! -d $dir ]] ; then continue ; fi
   for file in $dir ; do 
      echo $file 
   done 
done
