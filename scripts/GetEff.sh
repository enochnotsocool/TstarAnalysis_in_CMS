#-------------------------------------------------------------------------------
#
#   File        : GetEff.sh
#   Descriptions: 
#      Getting the selection efficiency of the all the histogram in 
#      Designated directory
#   Usage       : ./GetEff.sh Option
#
#-------------------------------------------------------------------------------
#!/bin/bash

HIST_NAME=""

function main(){
   HIST_NAME=$1
   for dir in * ; do 
      if [[  ! -d $dir  ]]; then continue ; fi
      echo "In directory $dir..."
      makeMacros $dir 
      runMacros  $dir 
   done 
}

function makeMacros() {
   local dir=$1
   local fileList=$( ls $dir );
   local loadCmd=""
   local readCmd=""
   local i=0
   for file in $fileList ; do
      if [[ $file != *".root" ]] ; then  continue; fi
      loadCmd=$loadCmd"TFile* _file${i} = TFile::Open( \"$file\" );\n";
      readCmd=$readCmd"TH1F*  _hist${i} = (TH1F*)( _file${i}->Get( \"$HIST_NAME\" ));\n"
      readCmd=$readCmd"Hist->Add( _hist${i} ); \n"
      ((i++))
   done
   #echo $loadCmd
   #echo $readCmd

   echo   "#include \"TH1F.h\"" > $dir/macro.cc
   echo   "void macro() { " >> $dir/macro.cc 
   echo   "TH1F* Hist = new TH1F( \"a\", \"a\", 10 , 0 , 10  );" >> $dir/macro.cc
   echo -e $loadCmd >> $dir/macro.cc
   echo -e $readCmd >> $dir/macro.cc
   echo   " printf(\"%0.12lf , %lf \\n\\n\", Hist->GetBinContent(7)/Hist->GetBinContent(1) , Hist->GetBinContent(1));" >> $dir/macro.cc 
   echo "}" >> $dir/macro.cc
}

function runMacros(){
   local dir=$1
   cd $dir 
   root -l -b -q macro.cc
   cd -
}

main $@
