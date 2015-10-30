#-------------------------------------------------------------------------------
#
#   File        : makeBranchClass.sh
#   Descriptions: Reading from files to generate branch class
#   Usage       : ./makeBranchClass.sh 
#
#-------------------------------------------------------------------------------
#!/bin/bash

HEADERFILE_DIR="./interface"
PARTICLE_HEAD_DIR="./interface_read"
WRITE_IMP_DIR="./src"
READ_IMP_DIR="./src_read"

function main() {
   makeParticle Electron
   makeParticle Event 
   makeParticle Muon
   makeParticle Jet
}

function makeParticle() {
   filename=${1}.txt
   branch_headerFile="./interface/Mini${1}Branches.h"
   branch_writeFile="./src/Mini${1}Branches_write.cc"
   branch_readFile="./src_read/Mini${1}Branches_read.cc"
   particle_header="./interface_read/Mini${1}.h"
   particle_file="./src_read/Mini${1}.cc"
   makeHeader ${1} ${branch_headerFile}
   makeWriteFile ${1} ${branch_writeFile}
   makeReadFile ${1} ${branch_readFile}
   makeParticleHead ${1} ${particle_header}
   makePartcleFile ${1} $particle_file
}

function makeHeader(){
   DataTypeList=""
   while read -r line; do
      var_type=$( echo $line | awk '{print $1}')
      var_name=$( echo $line | awk '{print $2}')
      if [[ $1 != Event ]]; then
         DataTypeList=$DataTypeList"\n   std::vector<$var_type> _${var_name}List;"
      else
         DataTypeList=$DataTypeList"\n   $var_type _${var_name};"
      fi
   done < ${1}.txt
   cat ./templates/ParticleBranchesHeader.h | 
      sed "s@PARTICLE@${1}@"      |
      sed "s@__DATA_MEMBERS__@$DataTypeList@" > $2 
}

function makeWriteFile() {
   registerCMDs=""
   clearCMDS=""
   while read -r line ; do 
      var_name=$( echo $line | awk '{print $2}' );
      if [[ $1 != Event ]]; then
         registerCMDs=$registerCMDs"\n   tree->Branch( \"${1}$var_name\" , \&_${var_name}List );"
         clearCMDS=$clearCMDS"\n   _${var_name}List.clear();"
      else
         registerCMDs=$registerCMDs"\n   tree->Branch( \"${1}$var_name\" , \&_${var_name} );"
      fi
   done < ${1}.txt
   cat ./templates/ParticleBranchesWrite.h |
      sed "s@PARTICLE@${1}@g" |
      sed "s@__REGISTER_CMDS__@$registerCMDs@" |
      sed "s@__CLEAR_CMDS__@$clearCMDS@" > $2
}

function makeReadFile() {
   readCMDs=""
   while read -r line ; do 
      var_name=$( echo $line | awk '{print $2}' );
      if [[ $1 != Event ]]; then
         readCMDs=$readCMDs"\n   tree->SetBranchAddress( \"${1}$var_name\" , \&_${var_name}List );"
      else
         readCMDs=$readCMDs"\n   tree->SetBranchAddress( \"${1}$var_name\" , \&_${var_name} );"
      fi
   done < ${1}.txt
   cat ./templates/ParticleBranchesRead.h | 
      sed "s@PARTICLE@${1}@g" |
      sed "s@__READ_CMDS__@$readCMDs@" > $2
}

function makeParticleHead() {
   accessFunction=""
   while read -r line ; do 
      var_type=$( echo $line | awk '{print $1}')
      var_name=$( echo $line | awk '{print $2}' );
      accessFunction=$accessFunction"\n  const $var_type\& $var_name();"
   done < ${1}.txt
   cat ./templates/Particle.h |
      sed "s@PARTICLE@${1}@g" |
      sed "s@__ACCESS_FUNCTIONS__@${accessFunction}@" > ${2}
}

function makePartcleFile() {
   accessFunction=""
   while read -r line ; do 
      var_type=$( echo $line | awk '{print $1}')
      var_name=$( echo $line | awk '{print $2}' );
      accessFunction=$accessFunction"const $var_type\& Mini${1}::$var_name() { return ${1}Branches._${var_name}List[ _index ]; }"
   done < ${1}.txt
   cat ./templates/Particle.cc |
      sed "s@PARTICLE@${1}@g" |
      sed "s@__ACCESS_FUNCTIONS__@${accessFunction}@" > ${2}
}

main $@
