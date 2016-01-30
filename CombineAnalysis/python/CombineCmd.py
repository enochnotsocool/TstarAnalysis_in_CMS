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
   initfile_opts = argparse.ArgumentParser( description='Read single initialization file')
   initfile_opts.add_argument('mode',help='Initialization mode', typestr
   initfile_opts.add_argument('initfile',help='Initialization file to use',type=file )

   def do_Initialize(self,line):
      try:
         options = self.initfile_opts.parse_args(line.split())
      except:
         print "Error parsing arguments!", line
         return CmdExecStatus.OPTION_ERROR
      self.my_Combine.InitPlots(options.initfile.name)
      print "Done!"
      return CmdExecStatus.EXECUTE_SUCESS

   #----- Initialize available plots -------------------------------------------------------------------
   def do_InitPlots(self,line):
      try:
         options = self.initfile_opts.parse_args(line.split())
      except:
         print "Error parsing arguments!", line
         return CmdExecStatus.OPTION_ERROR
      self.my_Combine.InitPlots(options.initfile.name)
      print "Done!"
      return CmdExecStatus.EXECUTE_SUCESS

   def help_InitPlots(self):
      print "Initialize the plots used in the analysis using input file"
      self.initfile_opts.print_help()

   def complete_InitPlots(self,text,line,begidx,endidx):
      return self.PathComplete(line,begidx,endidx)

   #----- Initialize available samples ----------------------------------------------------------------- 
   def do_InitSamples(self,line):
      try:
         options = self.initfile_opts.parse_args(line.split())
      except:
         print "Error parsing arguments!" , line 
         return CmdExecStatus.OPTION_ERROR
      self.my_Combine.InitSamples(options.initfile.name)
      print "Done!"
      return CmdExecStatus.EXECUTE_SUCESS
   
   def help_InitSamples(self):
      print "Initialize the samples used in the analysis using input files"
      self.initfile_opts.print_help()
   
   def complete_InitSamples(self,text,line,begidx,endidx):
      return self.PathComplete(line,begidx,endidx)

   #----- Initializing available channels --------------------------------------------------------------
   def do_InitChannels(self,line):
      try:
         options = self.initfile_opts.parse_args(line.split())
      except:
         print "Error parsing arguments", line
         return CmdExecStatus.OPTION_ERROR
      self.my_Combine.InitChannels(options.initfile.name)
      print "Done!"
      return CmdExecStatus.EXECUTE_SUCESS 

   def help_InitChannels(self):
      print "Defining the various channels used in the program"
      self.initfile_opts.print_help()

   def complete_InitChannels(self,text,line,begidx,endidx):
      return self.PathComplete(line,begidx,endidx)
   
   #------------------------------------------------------------------------------- 
   #   Channel initialization commands
   #------------------------------------------------------------------------------- 
   channel_init_opts = argparse.ArgumentParser( description = 'Passing single input file to channel for initialization' )
   channel_init_opts.add_argument('Mode'    , help='Which initialization to run' , type=str  )
   channel_init_opts.add_argument('Channel' , help='Channel to initialize'       , type=str  )
   channel_init_opts.add_argument('file'    , help='File to use'                 , type=file )

   def do_SetChannel(self,line):
      try:
         options = self.channel_init_opts.parse_args( line.split() )
      except:
         print "Error parsing arguments!", line 
         return CmdExecStatus.OPTION_ERROR
      attr = getattr( self.my_Combine , "SetChannel" + options.Mode )
      attr( options.Channel, options.file.name )
      return CmdExecStatus.EXECUTE_SUCESS

   def help_SetChannel(self):
      print "Defining aspects of a channel from a input file"
      self.channel_init_opts.print_help()
      print "\nDefined modes:"
      for mode in self.CompleteCombineFunc( 'SetChannel' ):
         print "\t", mode
      print "\nDefined Channels: "
      for channel in self.CompleteChannel(''):
         print "\t", channel 
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
      for channel in self.y_Combine.AvailableChannels() :
         if channel.startswith(text):
            ans.append(text)
      return ans;



if __name__ == "__main__":
   myCmd = CombineCmd()
   myCmd.cmdloop()
