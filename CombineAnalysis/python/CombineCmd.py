##**************************************************************************************************
##
##    FileName   :  CombineCmd.py
##    Description:  Command line interface for C++ combine manager class
##
##**************************************************************************************************

import sys
import os
import argparse
import inspect

sys.path.append( os.environ['CMSSW_BASE']+"/src/" )

from CMSSW_Utils.Utils_Types.pluginStdVector        import * ## For stl containers
from CMSSW_Utils.Utils_Types.CmdParser              import * ## For advanced cmd parser class
from CMSSW_Utils.Utils_Functions.utils_string       import * ## For additional string parsing
from TstarAnalysis.CombineAnalysis.pluginCombineMgr import * ## For self written C++ objects 
class CombineCmd( CmdParser ):
   prompt = 'tstar> '
   intro  = 'Session for running the tstar combination analysis'
   my_Combine = CombineMgr()

   #------------------------------------------------------------------------------- 
   #   Initialization commands
   #-------------------------------------------------------------------------------  
   def InitFileOpts(self):
       initfile_opts = argparse.ArgumentParser( description='Read single initialization file')
       initfile_opts.add_argument('mode', type=str, choices = self.CompleteCombineFunc('Init'),
               help = "Setting to initialize" )
       initfile_opts.add_argument('initfile', type=file,
               help='Initialization file to use')
       return initfile_opts

   def do_Initialize(self,line):
      try:
         options = self.InitFileOpts.parse_args(line.split())
      except:
         print "Error parsing arguments!", line
         return CmdExecStatus.OPTION_ERROR
      attr = getattr( my_Combine , "Init" + options.Mode );
      attr(options.initfile.name)
      print "Done!"
      return CmdExecStatus.EXECUTE_SUCESS

   def help_Initialize(self):
      self.InitFileOpts().print_help()
      print "\nDefined Modes:"
      for mode in self.CompleteCombineFunc('Init'):
         print '\t', mode 
      pass

   def complete_Initialize(self,text,line,begidx,endidx):
      wordidx = WordPositionAtIndex(line,begidx)
      if wordidx == 0 :
         return CompleteCombineFunc('Init',text)
      else
         return PathComplete(line,begidx,endidx)

   #------------------------------------------------------------------------------- 
   #   Channel initialization commands
   #-------------------------------------------------------------------------------
   def ChannelInitOpts(self):
      channel_init_opts = argparse.ArgumentParser( description = 'Passing single input file to channel for initialization' )
      channel_init_opts.add_argument('Mode'    , type=str  , choices = self.CompleteCombineFunc('SetChannel'),
              help = "Initialization mode" )
      channel_init_opts.add_argument('Channel' , type=str  , choices = self.CompleteChannel(),
              help = "Channel to initialize" )
      channel_init_opts.add_argument('file'    , type=file , help = 'Input file')
      return channel_init_opts

   def do_SetChannel(self,line):
      try:
         options = self.ChannelInitOpts().parse_args( line.split() )
      except:
         print "Error parsing arguments!", line 
         return CmdExecStatus.OPTION_ERROR
      attr = getattr( self.my_Combine , "SetChannel" + options.Mode )
      attr( options.Channel, options.file.name )
      return CmdExecStatus.EXECUTE_SUCESS

   def help_SetChannel(self):
      print "Defining aspects of a channel from a input file"
      self.channel_init_opts.print_help()
      pass

   def complete_SetChannel(self,text,line,begidx,endidx):
      wordidx = WordPositionAtIndex(line, begidx ) 
      if wordidx == 0 :
         return self.CompleteCombineFunc( "SetChannel" , text )
      elif wordidx == 1 :
         return self.CompleteChannel( text )
      else:
         return self.PathComplete(line,begidx,endidx)
       

   #------------------------------------------------------------------------------- 
   #   Listing commands 
   #------------------------------------------------------------------------------- 
   def do_ListAvailablePlot(self,line):
      plotlist = self.my_Combine.AvailablePlots();
      for plot in plotlist:
         print plot
      return CmdExecStatus.EXECUTE_SUCESS

   def do_ListAvailableSamples(self,line):
      sampleList = self.my_Combine.AvailableSamples()
      for sample in sampleList:
         print sample
      return CmdExecStatus.EXECUTE_SUCESS

   #------------------------------------------------------------------------------- 
   #   Completion helper functions 
   #-------------------------------------------------------------------------------
   def CompleteCombineFunc( self, prefix , text='' ):
      ans = []
      for name,stuff in inspect.getmembers( CombineMgr , predicate=inspect.ismethod ):
         if name.startswith( prefix  ):
            ans.append(name[len(prefix):])
      return ans;

   def CompleteChannel( self, text ):
      ans = [] 
      for channel in self.my_Combine.AvailableChannels() :
         if channel.startswith(text):
            ans.append(text)
      return ans;



if __name__ == "__main__":
   myCmd = CombineCmd()
   myCmd.cmdloop()
