import sys
import os

sys.path.append( os.environ['CMSSW_BASE']+"/src/" )

from TstarAnalysis.CombineAnalysis.CombineCmd import * ## Importing advance Cmd instance 

if __name__ == '__main__':
   mycmd = CombineCmd()
   mycmd.cmdloop()
