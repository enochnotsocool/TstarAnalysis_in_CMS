#-------------------------------------------------------------------------------
#
#   File        : Run_All.sh
#   Descriptions: Run all samples listed in ./DataSetList.txt
#   Usage       : ./Run_All.sh
#
#-------------------------------------------------------------------------------
#!/bin/bash

for dataset in $(cat ./MCSetList.asc ); do
   ./RunSample.sh $dataset
done
