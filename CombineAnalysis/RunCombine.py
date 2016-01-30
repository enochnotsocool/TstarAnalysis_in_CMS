##**************************************************************************************************
##
##    FileName   :  RunCombine.py
##    Description:  Command line like interface for tstar analysis
##
##**************************************************************************************************
import sys
import os
import argparse 

sys.path.append( os.environ['CMSSW_BASE']+"/src/" )

from TstarAnalysis.CombineAnalysis.CombineCmd import * ## Importing advance Cmd instance 

sysarg = argparse.ArgumentParser( description = 'Running RunCombine.py from commands line' )
sysarg.add_argument( '-f', '--file' , type=file , nargs='+', 
      help = 'File to run at launch' )

if __name__ == '__main__':
   mycmd = CombineCmd()
   options = sysarg.parse_args()
   for x in options.file :
      command = 'runfile ' + x.name
      command = mycmd.precmd( command )
      status  = mycmd.onecmd( command )
      if status == CmdExecStatus.TERMINATE_SIG :
         sys.exit()
   mycmd.cmdloop()
