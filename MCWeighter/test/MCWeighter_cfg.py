import FWCore.ParameterSet.Config as cms

#------------------------------------------------------------------------------- 
#   Options settings
#------------------------------------------------------------------------------- 
import FWCore.ParameterSet.VarParsing as opts
import copy

options = opts.VarParsing ('analysis')
options.setDefault( 'maxEvents' , 10000 );

options.register('Debug',
      0,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.int,
      'Debugging output level' )

options.register("filename",
      "ntuple.root",
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Histogram filename')

options.parseArguments()

#------------------------------------------------------------------------------- 
#   Setting up process
#------------------------------------------------------------------------------- 
process = cms.Process("LHEWeighter")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.categories.append('HLTrigReport')

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )
process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring(
      # 'file:/wk_cms/yichen/miniAODs/MC_reMiniAOD_25ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root'
       'file:/wk_cms/yichen/miniAODs/MC_reMiniAOD_25ns/TTJets_amcatnlo.root'
         )
      )

#process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")
process.GlobalTag.globaltag="74X_mcRun2_asymptotic_v2"

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
