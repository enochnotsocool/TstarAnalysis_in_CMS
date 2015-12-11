import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts
import TstarAnalysis.BaseClasses.CommonOptions as COpts 
import TstarAnalysis.BaseClasses.ProcessParser as myParser
import copy

options = opts.VarParsing ('analysis')

COpts.initOptions( options );

options.setDefault('sample', 'file:/wk_cms/yichen/TstarAnalysis/filtered_MiniAODs/SignalMC.root')
options.setDefault('DataProcessing', "MC25ns_MiniAODv2" )
options.setDefault('Debug', 10 )

options.parseArguments()

#------------------------------------------------------------------------------- 
#   Setting up process
#------------------------------------------------------------------------------- 
process = cms.Process("TstarNtuplizer")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.MessageLogger.categories.append('HLTrigReport')

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )
process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring(
         options.sample
         )
      )

#process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")

process.GlobalTag.globaltag=myParser.getGlobalTag( options.DataProcessing )

#------------------------------------------------------------------------------- 
#   Egamma ID pre-requisites
#-------------------------------------------------------------------------------
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

my_elid_modules      = myParser.getElectronIDModule( options.DataProcessing )
elec_loose_id_label  = myParser.getElectronIDLabel( "loose" , options.DataProcessing )
elec_medium_id_label = myParser.getElectronIDLabel( "medium", options.DataProcessing )

setupAllVIDIdsInModule(process,my_elid_modules ,setupVIDElectronSelection)


#------------------------------------------------------------------------------- 
#   ED analyzer settings
#------------------------------------------------------------------------------- 
from TstarAnalysis.BaseClasses.DefaultObjectSelection import * 

process.TFileService = cms.Service("TFileService",
      fileName = cms.string( options.outputLabel )
      )

process.ntuplizer = cms.EDAnalyzer(
      "ggChannel_Ntuplizer",
      ObjectSelectionParameter = DefaultObjectSelection,  
      eleLooseIdMap   = cms.InputTag( elec_loose_id_label  ) ,
      eleMediumIdMap  = cms.InputTag( elec_medium_id_label ) ,
      Debug = cms.untracked.int32( options.Debug ),
   )


process.outpath = cms.EndPath(
      process.egmGsfElectronIDSequence * 
      process.ntuplizer
      )
