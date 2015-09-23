import FWCore.ParameterSet.Config as cms

#------------------------------------------------------------------------------- 
#   Options settings
#------------------------------------------------------------------------------- 
import FWCore.ParameterSet.VarParsing as opts
options = opts.VarParsing ('analysis')

options.register('maxEvts',
      -1,# default value: process all events
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.int,
      'Number of events to process')

options.register('globalTag',
      'MCRUN2_74_V9',
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Global Tag')

options.register('sample',
      '/store/mc/RunIISpring15DR74/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/F884E560-CE09-E511-95DB-00266CF3DE70.root',
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Sample to analyze')

options.register('Debug',
      0,# default value: no messages
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.int,
      'debug level')

#------------------------------------------------------------------------------- 
#   Process definitions
#------------------------------------------------------------------------------- 
process = cms.Process("EventAnalyzer")
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 1000 ) )
process.load("FWCore.MessageService.MessageLogger_cfi")
process.options.allowUnscheduled = cms.untracked.bool(True)

process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring( options.sample )
      )

process.demo = cms.EDAnalyzer('EventAnalyzer')

process.TFileService = cms.Service("TFileService", fileName = cms.string( "results.root" ) )

process.p = cms.Path(process.demo)
