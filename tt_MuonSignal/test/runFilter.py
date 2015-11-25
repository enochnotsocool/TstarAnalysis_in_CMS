import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts
import TstarAnalysis.BaseClasses.CommonOptions as myOptions

options = opts.VarParsing ('analysis')

options.register('maxEvts',
      1000, ## For all events processing use -1
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.int,
      'Number of events to process')

options.register('sample',
      'file:///wk_cms/yichen/miniAODs/Run2015_reMiniAOD/Run2015D_SingleMuon.root',
      opts.VarParsing.multiplicity.list,
      opts.VarParsing.varType.string,
      'Sample to analyze')

options.register('outputLabel',
      'myTuple.root',
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Output label')

options.register('DataProcessing',
      "Data25ns",
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Data processing type')

options.register('useNoHFMET',
      True,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.bool,
      'Adding met without HF and relative jets')

options.register('usePrivateSQLite',
      True,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.bool,
      'Take Corrections from private SQL file')

options.register('forceResiduals',
      None,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.bool,
      'Whether to force residuals to be applied')

options.register('Debug',
      0,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.int,
      'Debugging output level' )

options.register('b2gPreprocess',
      False,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.bool,
      'Where to use the filters and producers defined by b2g group')

options.register("histFile",
      "myHist.root",
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Histogram filename')

options.register('jsonFile',
      '',
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      "Golden Json file input" )

options.parseArguments()

#------------------------------------------------------------------------------- 
#   Basic options parsing
#------------------------------------------------------------------------------- 
useHFCandidates  = not options.useNoHFMET   #create an additionnal NoHF slimmed MET collection if the option is set to false
usePrivateSQlite = options.usePrivateSQLite #use external JECs (sqlite file)
##applyResiduals   = options.isData           #application of residual corrections. 
                                            #   Have to be set to True once the 13 TeV residual corrections are available. 
                                            #   False to be kept meanwhile. Can be kept to False later for private tests
                                            #   or for analysis checks and developments (not the official recommendation!).
if not (options.forceResiduals == None):
   applyResiduals = (options.forceResiduals == True)

#------------------------------------------------------------------------------- 
#   Setting up process
#------------------------------------------------------------------------------- 
process = cms.Process("ggMuonFilter")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.categories.append('HLTrigReport')

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvts) )
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

if options.DataProcessing=="MC50ns":
   process.GlobalTag.globaltag="74X_mcRun2_asymptotic50ns_v0"
elif options.DataProcessing=="MC25ns":
   process.GlobalTag.globaltag="74X_mcRun2_asymptotic_v2"
elif options.DataProcessing=="Data50ns":
   process.GlobalTag.globaltag="74X_dataRun2_reMiniAOD_v0"
elif options.DataProcessing=="Data25ns":
   process.GlobalTag.globaltag="74X_dataRun2_reMiniAOD_v0"
else:
   print "Choose any of the following options for 'DataProcessing'", "MC50ns,  MC25ns, Data50ns, Data25ns" 

#------------------------------------------------------------------------------- 
#   Egamma ID pre-requisites
#-------------------------------------------------------------------------------
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

mu_elid_modules = ""
elec_loose_id_label = ""
elec_medium_id_label = ""
if options.DataProcessing=="MC50ns" or options.DataProcessing=="MC25ns" :
   my_elid_modules = 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_PHYS14_PU20bx25_V2_cff'
   elec_loose_id_label  = "egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-loose"
   elec_medium_id_label = "egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium"
elif "Data50ns" in options.DataProcessing :
   my_elid_modules = 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_50ns_V2_cff'
   elec_loose_id_label  = "egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-loose"
   elec_medium_id_label = "egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-medium"
elif "Data25ns" in options.DataProcessing :
   my_elid_modules =  'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff' 
   elec_loose_id_label  = "egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-loose"
   elec_medium_id_label = "egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-medium"

setupAllVIDIdsInModule(process,my_elid_modules ,setupVIDElectronSelection)

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

#------------------------------------------------------------------------------- 
#   EDFilter settings
#------------------------------------------------------------------------------- 
process.TFileService = cms.Service("TFileService",
      fileName = cms.string( options.histFile )
      )

process.gg_MuonSignal = cms.EDFilter(
      "tt_MuonSignal",
      eleLooseIdMap   = cms.InputTag( elec_loose_id_label  ) ,
      eleMediumIdMap  = cms.InputTag( elec_medium_id_label ) ,
      JetPt     = cms.untracked.int32(30),
      JetNumber = cms.untracked.int32(4)
      )

process.p1 = cms.Path(
      process.egmGsfElectronIDSequence * 
      process.gg_MuonSignal
      )

process.outpath = cms.EndPath(
      process.out
      )
