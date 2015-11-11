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
      echo "MC25ns"
   elif [[ $1 == *"74X_mcRun2_asymptotic50ns_v0"* ]]; then
      echo "MC50ns"
   elif [[ $1 == *"74X_dataRun2_Prompt_v4"* ]]; then
      echo "DataRunD_PromptReco"
   elif [[ $1 == *"Run2015D-05Oct2015"*  ]]; then
      echo "DataRunD_re"
   elif [[ $1 == *"Run2015C_25ns"* ]]; then
      echo "DataRunC25ns"
   elif [[ $1 == *"05Oct2015"* ]]; then
      echo "Data50ns"
   fi
}

function getJsonFile(){
   if [[ $1 == *"Run2015"* ]]; then
      echo "$(pwd)/./Cert_246908-258750_25ns.json" 
   else 
      echo ""
   fi
}

