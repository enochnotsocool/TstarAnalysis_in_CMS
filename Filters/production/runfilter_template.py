import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts
import TstarAnalysis.BaseClasses.ProcessParser as myParser 

DataProcessing="__DATAPROCESSING__"
#------------------------------------------------------------------------------- 
#   Setting up process
#------------------------------------------------------------------------------- 
process = cms.Process("RunFilter")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.MessageLogger.categories.append('HLTrigReport')

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring( __SAMPLES__ ) )
import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = "__JSONFILE__" ).getVLuminosityBlockRange()

#process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")

process.GlobalTag.globaltag = myParser.getGlobalTag( DataProcessing )

#------------------------------------------------------------------------------- 
#   Egamma ID pre-requisites
#-------------------------------------------------------------------------------
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

my_elid_modules      = myParser.getElectronIDModule( DataProcessing )
elec_loose_id_label  = myParser.getElectronIDLabel( "loose"  , DataProcessing )
elec_medium_id_label = myParser.getElectronIDLabel( "medium" , DataProcessing )

setupAllVIDIdsInModule(process,my_elid_modules, setupVIDElectronSelection)

#------------------------------------------------------------------------------- 
#   Output Modules settings
#------------------------------------------------------------------------------- 
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning
process.out = cms.OutputModule(
      "PoolOutputModule",
      fileName = cms.untracked.string( "__OUTPUT_LABEL__" ),
      SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
      outputCommands = cms.untracked.vstring(
         "drop *",
         "keep *" # Update to keep everything just in case
         )
      )

from TstarAnalysis.BaseClasses.DefaultObjectSelection import *

#------------------------------------------------------------------------------- 
#   EDFilter settings
#------------------------------------------------------------------------------- 
process.TFileService = cms.Service("TFileService",
      fileName = cms.string( "__HIST_FILE__" )
      )


process.myFilter = cms.EDFilter(
      "__FILTER_TYPE__" ,
      ObjectSelectionParameters = DefaultObjectSelection.clone(),
      eleLooseIdMap   = cms.InputTag( elec_loose_id_label  ) ,
      eleMediumIdMap  = cms.InputTag( elec_medium_id_label ) ,
      )

process.p1 = cms.Path(
      process.egmGsfElectronIDSequence * 
      process.myFilter
      )

process.outpath = cms.EndPath(
      process.out
      )


