import FWCore.ParameterSet.Config as cms

process = cms.Process("ggChannelFilter")

process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
process.source = cms.Source("PoolSource",
          fileNames = cms.untracked.vstring('/store/cmst3/user/gpetrucc/miniAOD/Spring15MiniAODv2/CMSSW_7_4_12/miniAOD-TTJets_madgraphMLM_25ns-40k_PAT.root')
          )
## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.load("Configuration.StandardSequences.MagneticField_cff")

## Output Module Configuration (expects a path 'p')
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning
process.out = cms.OutputModule(
      "PoolOutputModule",
      fileName = cms.untracked.string('patTuple.root'),
      SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
      outputCommands = cms.untracked.vstring( )
      )

process.ggChannelFilter = cms.EDFilter(
      "ggChannelFilter",
      muonsrc = cms.InputTag( "slimmedMuons" ) ,
      elecsrc = cms.InputTag( "slimmedElectrons" ),
      jetsrc  = cms.InputTag( "slimmedJets" ), 
      metsrc  = cms.InputTag( "slimmedMETs" ) , 
      vertexsrc = cms.InputTag( "offlineSlimmedPrimaryVertices" )
      )

process.p1 = cms.Path(
      process.ggChannelFilter 
      )
process.outpath = cms.EndPath(
      process.out
      )
