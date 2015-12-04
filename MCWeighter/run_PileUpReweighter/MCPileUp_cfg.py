import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts

options = opts.VarParsing ('analysis')

options.register( "binCount" ,
      50,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.int,
      'bin for pileup');


process = cms.Process("MCPileup")

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
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/144F903B-B76E-E511-9823-002590747D90.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/16B06D9D-FB6E-E511-829B-02163E010EA9.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/186B26BC-A36E-E511-B220-00259073E3E0.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/18E22114-7A6E-E511-ABEE-0025905A6090.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/1E512CAC-FD6E-E511-82D9-02163E013D3D.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/1ED2C1BE-B16E-E511-8EE8-00259074AE3C.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/202AA884-976E-E511-9E1E-00505602078D.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/22CA12E6-FB6E-E511-B918-02163E00EA10.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/24574A5C-BA6E-E511-9E82-00259073E31C.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/24EC4040-736E-E511-BC2D-002618943809.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/2655EB45-FD6E-E511-A97C-02163E00F47B.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/26E1900D-786E-E511-B654-0025905964A2.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/286D8370-FD6E-E511-A435-02163E015C8E.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/2A8A19C1-B16E-E511-8B8E-00505602078A.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/2A9BC6C3-B46E-E511-8B3F-00259073E4CA.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/2ABFA88D-6C6E-E511-B34C-0025905822B6.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/2C38FD00-ED6E-E511-82BA-00266CF9C1EC.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/2E07071F-EF6E-E511-9233-008CFA007B98.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/2E864CC7-B46E-E511-B475-00505602077B.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/2E91754C-AB6E-E511-A346-00505602077F.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/305E86FE-A56E-E511-BDBB-005056020789.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/32284689-BC6E-E511-AFB6-00259073E3AC.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/329759D0-666E-E511-8F79-002590200B00.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/34498FF6-EC6E-E511-9E81-00266CFAE764.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/36497170-CB6E-E511-B757-0025905964CC.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/36CCBBDF-066F-E511-B9D5-20CF3019DEEE.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/36D6BC6F-CB6E-E511-9FD0-0025905A6060.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/36D77228-FC6E-E511-AEEE-02163E011C04.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/381729C3-B46E-E511-AB95-00259073E34A.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/38443470-066F-E511-8FF4-D48564593F64.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/3ADEEDC6-B46E-E511-819F-00259073E466.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/3C0B0BB1-E76E-E511-859B-001D09FDD80D.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/3E64174C-816E-E511-B031-0025905964A6.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/407AA8E8-086F-E511-8030-BCAEC5097201.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/40EC9400-ED6E-E511-91F0-00266CF9C1EC.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/42167C60-FC6E-E511-95F9-02163E013EAA.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/4281958F-6C6E-E511-8C57-003048FFD732.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/42AC33AE-066F-E511-8842-0025907FD430.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/42E36B8E-EE6E-E511-92A6-3417EBE64C0C.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/44072064-FD6E-E511-8D30-02163E011C03.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/44F8F47D-046F-E511-9122-B083FED0FFCF.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/460BBF19-FD6E-E511-8D70-02163E010EFD.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/48370411-986E-E511-85F5-002590574604.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/48B99C3C-706E-E511-A066-00261894388F.root',
'/store/mc/RunIISpring15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/48C2B950-FE6E-E511-B8E2-02163E016BB9.root'
    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string( "MCPileUp.root" )
)

process.demo = cms.EDAnalyzer(
   'PileUpReWeighter',
   pileupSrc = cms.InputTag( "slimmedAddPileupInfo" ),
   binCount  = cms.int32( options.binCount )
) 


process.p = cms.Path(process.demo)
