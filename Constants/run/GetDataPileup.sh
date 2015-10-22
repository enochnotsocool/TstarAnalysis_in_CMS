#-------------------------------------------------------------------------------
#
#   File        : GetDataPileup.sh
#   Descriptions: Simple Script to get Data Pile up information
#   Usage       : ./GetDataPileup.sh
#
#-------------------------------------------------------------------------------
#!/bin/bash

pileupCalc.py \
   -i Cert_JSON.txt \
   --inputLumiJSON=pileup_JSON_10-20-2015.txt \
   --calcMode true \
   --maxPileupBin 60 \
   --numPileupBins 60 \
   DataPileUp.root
