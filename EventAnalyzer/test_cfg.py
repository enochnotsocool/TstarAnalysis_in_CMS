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
      '/store/relval/CMSSW_7_4_0_pre9_ROOT6/RelValWpToENu_M-2000_13TeV/MINIAODSIM/MCRUN2_74_V7-v1/00000/4A75C5D1-DCD1-E411-BE48-002618943951.root',
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
process = cms.Process("Demo")
process.load("FWCore.MessageService.MessageLogger_cfi")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( options.maxEvts ) )

process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring( options.sample )
      )

process.demo = cms.EDAnalyzer('EventAnalyzer')

process.TFileService = cms.Service("TFileService",
      fileName = cms.string( "test.root" )
      )


process.p = cms.Path(process.demo)
