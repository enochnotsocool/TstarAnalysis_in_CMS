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

class CombineStatus():
   NONE            = 0
   INIT_PLOT       = 1
   INIT_SAMPLE     = 2
   INIT_CHANNEL    = 3
   MADE_BASE_PLOTS = 4


class CombineCmd( CmdParser ):
   prompt = 'tstar> '
   intro  = 'Session for running the tstar combination analysis'

   def __init__(self):
      self.my_Combine = CombineMgr()
      self.recommended_mode = ['Asymptotic']
      self.state = CombineStatus.NONE 

   
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
         options = self.InitFileOpts().parse_args(line.split())
      except:
         print "Error parsing arguments!", line
         return CmdExecStatus.OPTION_ERROR

      if options.mode == 'Samples' and self.state < CombineStatus.INIT_PLOT :
         print "Error! Plot has not yet been initialized!"
         return CmdExecStatus.EXECUTE_FAIL
      elif options.mode == 'Channels' and self.state < CombineStatus.INIT_SAMPLE :
         print "Error! Samples has not yet been initialized!"
         return CmdExecStatus.EXECUTE_FAIL

      attr = getattr( self.my_Combine , "Init" + options.mode );
      attr(options.initfile.name)
      if options.mode == 'Plots':
         self.state = CombineStatus.INIT_PLOT 
      elif options.mode == 'Samples':
         self.state = CombineStatus.INIT_SAMPLE
      else:
         self.state = CombineStatus.INIT_CHANNEL 

      print "Done!"
      return CmdExecStatus.EXECUTE_SUCESS

   def help_Initialize(self):
      self.InitFileOpts().print_help()
      pass

   def complete_Initialize(self,text,line,begidx,endidx):
      wordidx = WordPositionAtIndex(line,begidx)
      if wordidx == 1 :
         return self.CompleteCombineFunc('Init',text)
      else:
         return self.PathComplete(line,begidx,endidx)

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
      if self.state < CombineStatus.INIT_CHANNEL:
         print "Error! You need to complete initialize the channels first!"
         return CmdExecStatus.EXECUTE_SUCESS
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
      self.ChannelInitOpts().print_help()
      pass

   def complete_SetChannel(self,text,line,begidx,endidx):
      wordidx = WordPositionAtIndex(line, begidx ) 
      if wordidx == 1 :
         return self.CompleteCombineFunc( "SetChannel" , text )
      elif wordidx == 2 :
         return self.CompleteChannel( text )
      else:
         return self.PathComplete(line,begidx,endidx)
       
   
   #------------------------------------------------------------------------------- 
   #   Validation plots making commands
   #------------------------------------------------------------------------------- 
   def do_MakeBasicPlots( self, line ):
      if self.state < CombineStatus.INIT_CHANNEL:
         print "Error! You need to initialize the channels first!"
         return CmdExecStatus.EXECUTE_FAIL
      self.my_Combine.MakeBasicPlots()
      self.state = CombineStatus.MADE_BASE_PLOTS 
      return CmdExecStatus.EXECUTE_SUCESS

   def DataBgOpts(self):
      databg_opts = argparse.ArgumentParser(description = 'Making a single data/MC background comparison plot' )
      databg_opts.add_argument( "channel" , type=str, choices = self.my_Combine.AvailableChannels() ,
            help='Channel to run' )
      databg_opts.add_argument( "plot" , type=str, choices = self.my_Combine.AvailablePlots(),
            help='Variable to plot' )
      return databg_opts 

   def do_MakeDataBGPlot( self, line ):
      if self.state < CombineStatus.MADE_BASE_PLOTS :
         print "Error! You need to run MakeBasicPlots first!"
         return CmdExecStatus.EXECUTE_FAIL 
      try:
         options = self.DataBgOpts().parse_args( line.split() )
      except:
         return CmdExecStatus.OPTION_ERROR 
      self.my_Combine.MakeDataBGPlot( options.channel , options.plot )
      return CmdExecStatus.EXECUTE_SUCESS 
   
   def help_MakeDataBGPlot(self):
      self.DataBgOpts().print_help()
      pass

   def complete_MakeDataBGPlot(self,text,line,begidx,endidx):
      wordidx = WordPositionAtIndex(line,begidx)
      if wordidx == 1 :
         return self.CompleteChannel(text)
      elif wordidx == 2:
         return self.CompletePlot(text)
      else:
         return []

   #------------------------------------------------------------------------------- 
   #   Higgs Combine commands
   #-------------------------------------------------------------------------------  
   def SingleChannelOpts(self):
      sigch_opts = argparse.ArgumentParser(description = 'Receives a single channel as argument' )
      sigch_opts.add_argument('channel', type=str, choices = self.my_Combine.AvailableChannels() )
      return sigch_opts

   def do_HC_MakeRequirements(self,line):
      if self.state < CombineStatus.MADE_BASE_PLOTS:
         print "Error! You need to run MakeBasicPlots first!"
         return CmdExecStatus.EXECUTE_FAIL 
      try:
         options = self.SingleChannelOpts().parse_args(line.split())
      except:
         return CmdExecStatus.OPTION_ERROR
      self.my_Combine.HC_MakeRequirements( options.channel )
      return CmdExecStatus.EXECUTE_SUCESS

   def help_HC_MakeRequirements(self):
      self.SingleChannelOpts().print_help()
      pass
   
   def complete_HC_MakeRequirements(self,text,line,begidx,endidx):
      wordidx = WordPositionAtIndex(line,begidx)
      if wordidx == 1 :
         return self.CompleteChannel(text)
      else:
         return []

   def RunCombineOpts(self):
      runcomb_opts = argparse.ArgumentParser(description = 'Receives channel and higg combine run options' )
      runcomb_opts.add_argument('channel',type=str, choices = self.my_Combine.AvailableChannels() ,
            help = 'Channel to run with' )
      runcomb_opts.add_argument('mode', type=str, choices = self.recommended_mode ,
            help = 'Allow modes for running higgs combine package' )
      return runcomb_opts 

   def do_HC_RunCombine(self,line):
      if self.state < CombineStatus.INIT_CHANNEL :
         print "Error! You need to initialized the channels first!"
         return CmdExecStatus.EXECUTE_FAIL
      try:
         options = self.RunCombineOpts().parse_args( line.split() )
      except:
         print "Error parsing errors!" 
         return CmdExecStatus.OPTION_ERROR 
      self.my_Combine.HC_RunCombine( options.channel , options.mode )
      return CmdExecStatus.OPTION_ERROR 

   def help_HC_RunCombine(self):
      self.RunCombineOpts().print_help()
      pass

   def complete_HC_RunCombine(self,text,line,begidx,endidx):
      wordidx = WordPositionAtIndex(line,begidx)
      if wordidx == 1 :
         return self.CompleteChannel(text)
      elif wordidx == 2:
         ans = []
         for method in self.recommended_mode:
            if method.startswith(method):
               ans.append(method)
         return ans;
      else:
         return []

   def do_HC_PlotLimit(self,line):
      if self.state < CombineStatus.INIT_CHANNEL :
         print "Error! You need to initialized the channels first!"
         return CmdExecStatus.EXECUTE_FAIL
      try:
         options = self.RunCombineOpts().parse_args( line.split() )
      except:
         return CmdExecStatus.OPTION_ERROR 
      self.my_Combine.HC_PlotLimit( options.channel , options.mode )
      return CmdExecStatus.OPTION_ERROR

   def help_HC_PlotLimit(self):
      self.RunCombineOpts().print_help()
      pass

   def complete_HC_PlotLimit(self,text,line,begidx,endidx):
      return self.complete_HC_RunCombine(text,line,begidx,endidx)

   #------------------------------------------------------------------------------- 
   #   Listing commands 
   #------------------------------------------------------------------------------- 
   def do_ListAvailablePlots(self,line):
      for plot in self.my_Combine.AvailablePlots():
         print plot
      return CmdExecStatus.EXECUTE_SUCESS

   def do_ListAvailableSamples(self,line):
      for sample in self.my_Combine.AvailableSamples():
         print sample
      return CmdExecStatus.EXECUTE_SUCESS
   
   def do_ListAvailableChannels(self,line):
      for channel in self.my_Combine.AvailableChannels():
         print channel
      return CmdExecStatus.EXECUTE_SUCESS

   #------------------------------------------------------------------------------- 
   #   Completion helper functions 
   #-------------------------------------------------------------------------------
   def CompleteCombineFunc( self, prefix , text='' ):
      ans = []
      mytext = text.lstrip().rstrip()
      for name,stuff in inspect.getmembers( CombineMgr , predicate=inspect.ismethod ):
         if name.startswith( prefix+mytext  ):
            ans.append(name[len(prefix):])
      return ans;

   def CompleteChannel( self, text='' ):
      ans = [] 
      for channel in self.my_Combine.AvailableChannels() :
         if channel.startswith(text):
            ans.append(channel)
      return ans;

   def CompletePlot( self, text='' ):
      ans = []
      for plot in self.my_Combine.AvailablePlots() :
         if plot.startswith(text):
            ans.append(plot)
      return ans;



if __name__ == "__main__":
   myCmd = CombineCmd()
   myCmd.cmdloop()
