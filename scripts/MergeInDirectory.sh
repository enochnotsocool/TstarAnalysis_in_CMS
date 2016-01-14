#-------------------------------------------------------------------------------
#
#   File        : MergeInDirectory.sh
#   Descriptions: Merge all edm files in one directory
#   Usage       : ./MergeInDirectory.sh [output/path] [path/to/directory]
#
#-------------------------------------------------------------------------------

function MergeInDirectory() 
{
   outputpath=$1
   dir_to_merge=$2
   fileList="inputFiles="
   for file in $(ls $dir_to_merge/*.root ); do
      file_path=$(readlink -f $file);
      fileList=$fileList"file:///$file_path,"
   done
   fileList=${fileList%,}
   echo $fileList
   edmCopyPickMerge $fileList outputFile=$outputpath
}


