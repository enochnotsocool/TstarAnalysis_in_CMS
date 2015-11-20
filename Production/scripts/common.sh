#-------------------------------------------------------------------------------
#
#   File        : common.sh
#   Descriptions: Common functions used through-out
#
#-------------------------------------------------------------------------------
#!/bin/bash 

function getFullName()
{
   local dataset=$1
   queryRaw=$( das_client --query="dataset=$dataset"  | grep '/.*/.*/.*' | head -n 1 )
   echo $queryRaw
}

function getDataSetName()
{
   local dataset=$1
   echo $dataset | awk -F "/" '{print $2"_"$3 }'  
}

function getDataProcess()
{
   if [[ $1 == *"74X_mcRun2_asymptotic_v2"* ]]; then
      echo "MC25ns_MiniAODv2"
   elif [[ $1 == *"74X_mcRun2_asymptotic50ns_v0"* ]]; then
      echo "MC50ns_MiniAODv2"
   elif [[ $1 == *"Run2015D-PromptReco-v4"* ]]; then
      echo "Data25ns_PromptRecov4"
   elif [[ $1 == *"Run2015D-05Oct2015"*  ]]; then
      echo "Data25ns_ReReco"
   elif [[ $1 == *"Run2015C_25ns"* ]]; then
      echo "Data25ns_MiniAODv2"
   elif [[ $1 == *"05Oct2015"* ]]; then
      echo "Data5ns_MiniAODv2"
   fi
}

function getJsonFile(){
   if [[ $1 == *"Run2015"* ]]; then
      echo "$(pwd)/./Cert_25ns_Latest.json" 
   else 
      echo ""
   fi
}

