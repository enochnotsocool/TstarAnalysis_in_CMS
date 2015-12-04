#**************************************************************************************************
#
#    FileName   :  FilterParser.py
#    Description:  Quick parser for filter testing
#
#**************************************************************************************************

def SetRunData( options ):
   options.sample = "file:///wk_cms/yichen/miniAODs/Run2015D_PromptReco-v4/SingleMuon.root"
   options.Debug  = 100
   options.DataProcessing = "Data25ns_PromptRecov4"
   options.outputLabel    = "DataOutput.root"
   options.histFile       = "DataHist.root"
   options.maxEvents = -1

def SetRunMC( options ):
   options.sample = "file:///wk_cms/yichen/miniAODs/MC_reMiniAOD_25ns/TTJets_amcatnlo.root"
   options.Debug  = 100
   options.DataProcessing = "Data25ns_PromptRecov4"
   options.outputLabel    = "DataOutput.root"
   options.histFile       = "DataHist.root"
   options.maxEvents = -1



