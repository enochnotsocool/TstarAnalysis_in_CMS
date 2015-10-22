import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/001F4F14-786E-E511-804F-0025905A60FE.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/00B6C8DE-E76E-E511-AEDE-008CFA000BB8.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/0268EC15-ED6E-E511-A4F2-00266CFAE7E8.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/02774F35-E86E-E511-AF7C-008CFA001444.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/06CF1D64-FD6E-E511-A13C-02163E011C03.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/081543FD-EC6E-E511-8A47-7845C4FC374C.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/08BA5283-FD6E-E511-B078-02163E00F45F.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/0A749664-FE6E-E511-9799-02163E00F6B5.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/0AE49E2D-7C6E-E511-8DB8-0025905A48F2.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/0E0E20AC-A36E-E511-A2DB-00259073E34E.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/1044447A-976E-E511-A4F6-00505602077E.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/10575350-816E-E511-8AFA-0025905A612A.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/12388530-786E-E511-990B-0025905A60E0.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/126046FF-EC6E-E511-95BE-001D09FDD6AB.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/1277CC74-CB6E-E511-A754-0025905A6118.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/128BA9A2-066F-E511-908F-00259057490C.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/129F603B-B76E-E511-A170-002590747DC8.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/12A973BF-B16E-E511-89A9-00259073E3E0.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/12D34163-7A6E-E511-A97B-0025905A60AA.root',
     '/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/144F903B-B76E-E511-9823-002590747D90.root'
    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string( "MCPileUp.root" )
)

process.demo = cms.EDAnalyzer(
   'MCPileUp',
   pileupSrc = cms.InputTag( "slimmedAddPileupInfo" )
)


process.p = cms.Path(process.demo)
