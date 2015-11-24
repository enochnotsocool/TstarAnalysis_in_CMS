#-------------------------------------------------------------------------------
#
#   File        : compute.sh
#   Descriptions: Commands for getting the information for pileup reweighting
#
#-------------------------------------------------------------------------------
#!/bin/bash

PILEUP_BINCOUNT=50

echo "Copying file from lxplus machine!"
scp ${USER}@lxplus6.cern.ch:/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/PileUp/pileup_latest.txt ./pileup.json 

echo "Computing Data pile up using pileupCalc.py tool!"
pileupCalc.py                       \
   -i Cert_25ns_Latest.json         \
   --inputLumiJSON pileup.json      \
   --calcMode true                  \
   --minBiasXsec 69000              \
   --maxPileupBin  $PILEUP_BINCOUNT \
   --numPileupBins $PILEUP_BINCOUNT \
   DataPileUp.root

echo "Computing MC pile up using self written class!"
cmsRun MCPileUp_cfg.py binCount=$PILEUP_BINCOUNT

echo "Running to compare MC with Data!"
root -q compare.cc > PileUpScale.txt
