import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts
import TstarAnalysis.BaseClasses.CommonOptions as COpts
import TstarAnalysis.BaseClasses.ProcessParser as myParser 

options = opts.VarParsing('analysis')
COpts.initOptions( options )

options.register( "Type",
   "gg_MuonSignal", 
   opts.VarParsing.multiplicity.singleton,
   opts.VarParsing.varType.string,
   "Filter Type to Run" )

options.register( "histFile" , 
      "myHist.root",
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      "Filename of histogram" )

options.register( "RunMC" ,
      False,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.bool,
      "Quick Option for testing MC" )

options.register( "RunData" ,
      False,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.bool,
      "Quick option for testing Data" )

options.parseArguments()

#------------------------------------------------------------------------------- 
#   Quick Data Parsing
#-------------------------------------------------------------------------------
from TstarAnalysis.Filters.FilterParser import *
if options.RunMC :
   SetRunMC( options )
elif options.RunData:
   SetRunData( options )

#------------------------------------------------------------------------------- 
#   Setting up process
#------------------------------------------------------------------------------- 
process = cms.Process("FilterTest")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.MessageLogger.categories.append('HLTrigReport')

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring( options.sample ) )
import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = options.jsonFile ).getVLuminosityBlockRange()

#process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")

process.GlobalTag.globaltag = myParser.getGlobalTag( options.DataProcessing )

#------------------------------------------------------------------------------- 
#   Egamma ID pre-requisites
#-------------------------------------------------------------------------------
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

my_elid_modules = ""
elec_loose_id_label = ""
elec_medium_id_label = ""
my_elid_modules      = myParser.getElectronIDModule( options.DataProcessing )
elec_loose_id_label  = myParser.getElectronIDLabel( "loose"  , options.DataProcessing )
elec_medium_id_label = myParser.getElectronIDLabel( "medium" , options.DataProcessing )

setupAllVIDIdsInModule(process,my_elid_modules, setupVIDElectronSelection)

#------------------------------------------------------------------------------- 
#   Output Modules settings
#------------------------------------------------------------------------------- 
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning
process.out = cms.OutputModule(
      "PoolOutputModule",
      fileName = cms.untracked.string( options.outputLabel ),
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
      fileName = cms.string( options.histFile )
      )


process.myFilter = cms.EDFilter(
      options.Type ,
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

