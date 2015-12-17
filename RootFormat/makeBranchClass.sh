#-------------------------------------------------------------------------------
#
#   File        : makeBranchClass.sh
#   Descriptions: Reading from files to generate branch class
#   Usage       : ./makeBranchClass.sh 
#
#-------------------------------------------------------------------------------
#!/bin/bash

HEADERFILE_DIR="./interface"
WRITE_IMP_DIR="./src/"
READ_IMP_DIR="./src/"
VARLIST_DIR="./variableList/"

TARGETLIST="Event Electron Muon Jet HitFit"


makeBranchName() 
{
   target=$1
   vartype=$2
   varname=$3
   varsize=$4

   echo "\"${target}.${varname}\""; 
}

makeAddress()
{
   target=$1
   vartype=$2
   varname=$3
   varsize=$4

   if [[ $varsize == ""  ]] ; then 
      echo "\&$varname"; 
   else
      echo "$varname"
   fi 
}

makeLeafName()
{
   target=$1
   vartype=$2
   varname=$3
   varsize=$4

   
   ## Getting character flag
   if [[ $vartype == "Int_t" ]] ; then
      typeToken=I
   elif [[ $vartype == "UInt_t" ]]; then
      typeToken=i
   elif [[ $vartype == "Float_t" ]] ; then   
      typeToken=F
   elif [[ $vartype == "Bool_t" ]] ; then
      typeToken=O
   elif [[ $vartype == "Char_t" ]] ; then 
      typeToken=C
   elif [[ $vartype == "ULong64_t" ]] ; then 
      typeToken=l
   else 
      echo $UNKNOWN_STRING
      exit -1;
   fi

   if [[ $varsize == "" ]]; then
      echo "\"${target}.$varname/$typeToken\""
   else 
      echo "\"${target}.$varname[${target}.Size]/$typeToken\"";
   fi 
}



for target in $TARGETLIST ; do 
   varfile="${VARLIST_DIR}/${target}.cc"
   if [[ ! -f ${varfile} ]]; then
      echo "Skipping Branches for $target! File ${varfile} doesn't exist!"
      continue;
   fi
   
   #-----  Making header  ---------------------------------------------------------
   headerfile=${HEADERFILE_DIR}/${target}Branches.h
   sed "s@OBJECT@${target}@" ./templates/BranchesHeader.h |
   sed -e "/__DATA_MEMBERS__/r $varfile" |
   sed -e "/__DATA_MEMBERS__/d" |
   cat > ${headerfile}
   astyle --suffix=none ${headerfile}

   #-----  Making stripped down files  --------------------------------------------
   sed 's|/\*|\n&|g;s|*/|&\n|g' $varfile |
   sed '/\/\*/,/*\//d'  |  ## Removing multi-line comments
   sed 's@//.*@@'       |  ## Remove single line comment
   sed 's@\[\s*@ [@'    |  ## Ensuring array declaration spacing
   sed 's@\s*\]@]@'     |  ## Ensuring array declaration spacing
   sed 's@;@@'          |  ## Stripping semicolons
   sed '/^\s*$/d'       |  ## Stripping blank lines
   cat > temp.txt

   #-----  Making read/write commands  -------------------------------------------------
   writecmd=""
   readcmd=""
   while read line ; do 
      wordlist=( $line )
      vartype=${wordlist[0]}; varname=${wordlist[1]}; varsize=${wordlist[2]}

      branchName=$( makeBranchName $target $vartype $varname $varsize)
      address=$(    makeAddress    $target $vartype $varname $varsize)
      leafname=$(   makeLeafName   $target $vartype $varname $varsize)

      if [[ $leafname == "" ]]; then
         writecmd=$writecmd"\ntree->Branch($branchName,$address );"
      else
         writecmd=${writecmd}"\ntree->Branch($branchName,$address,$leafname);"
      fi
      readcmd=${readcmd}"\ntree->SetBranchAddress($branchName,$address);"
   done < temp.txt

   #-----  Making writing file  ---------------------------------------------------
   writefile=${WRITE_IMP_DIR}/${target}Branch.cc
   sed "s@OBJECT@$target@" ./templates/BranchesWrite.cc |
   sed -e "s@__REGISTER_CMDS__@${writecmd}@" |
   cat > $writefile 
   astyle --suffix=none ${writefile}
   
   #-----  Making reading file  ---------------------------------------------------
   writefile=${READ_IMP_DIR}/${target}Branch_read.cc
   sed "s@OBJECT@$target@" ./templates/BranchesRead.cc |
   sed -e "s@__READ_CMDS__@${readcmd}@" |
   cat > $writefile 
   astyle --suffix=none ${writefile}

done

