import FWCore.ParameterSet.Config as cms

#------------------------------------------------------------------------------- 
#   Options settings
#------------------------------------------------------------------------------- 
import FWCore.ParameterSet.VarParsing as opts
import copy

options = opts.VarParsing ('analysis')

options.register('maxEvts',
      -1, ## For all events processing use -1
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.int,
      'Number of events to process')

options.register('sample',
      'file:/wk_cms/yichen/miniAODs/MC_reMiniAOD_25ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root',
      opts.VarParsing.multiplicity.list,
      opts.VarParsing.varType.string,
      'Sample to analyze')


options.register('DataProcessing',
      "MC25ns",
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

options.register("filename",
      "ntuple.root",
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Histogram filename')

options.parseArguments()

#------------------------------------------------------------------------------- 
#   Basic options parsing
#------------------------------------------------------------------------------- 
useHFCandidates  = not options.useNoHFMET   #create an additionnal NoHF slimmed MET collection if the option is set to false
usePrivateSQlite = options.usePrivateSQLite #use external JECs (sqlite file)
#applyResiduals   = options.isData           #application of residual corrections. 
                                            #   Have to be set to True once the 13 TeV residual corrections are available. 
                                            #   False to be kept meanwhile. Can be kept to False later for private tests
                                            #   or for analysis checks and developments (not the official recommendation!).
if not (options.forceResiduals == None):
   applyResiduals = (options.forceResiduals == True)

#------------------------------------------------------------------------------- 
#   Setting up process
#------------------------------------------------------------------------------- 
process = cms.Process("TstarNtuplizer")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.categories.append('HLTrigReport')

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvts) )
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
#   ED analyzer settings
#------------------------------------------------------------------------------- 
process.TFileService = cms.Service("TFileService",
      fileName = cms.string( options.filename )
      )

process.mcweighter = cms.EDAnalyzer(
      "MCWeighter",
   )


process.outpath = cms.EndPath(
      process.mcweighter
      )
