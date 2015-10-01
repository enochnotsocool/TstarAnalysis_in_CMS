import FWCore.ParameterSet.Config as cms

#------------------------------------------------------------------------------- 
#   Options settings
#------------------------------------------------------------------------------- 
import FWCore.ParameterSet.VarParsing as opts
import copy

options = opts.VarParsing ('analysis')

options.register('maxEvts',
      1000, ## For all events processing use -1
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.int,
      'Number of events to process')

options.register('sample',
      '/store/cmst3/user/gpetrucc/miniAOD/Spring15MiniAODv2/CMSSW_7_4_12/miniAOD-TTJets_madgraphMLM_25ns-40k_PAT.root',
      opts.VarParsing.multiplicity.list,
      opts.VarParsing.varType.string,
      'Sample to analyze')

options.register('lheLabel',
      'externalLHEProducer',
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'LHE module label')

options.register('outputLabel',
      'myHists.root',
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Output label')

options.register('globalTag',
      '', ## Optional, could be decided automatically
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Global Tag')

options.register('isData',
      False,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.bool,
      'Is data?')

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

options.register('LHE',
      False,
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.bool,
      'Keep LHEProducts')

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

options.parseArguments()

#------------------------------------------------------------------------------- 
#   Basic options parsing
#------------------------------------------------------------------------------- 
if(options.isData):options.LHE = False
runOnData        = options.isData           #data/MC switch
useHFCandidates  = not options.useNoHFMET   #create an additionnal NoHF slimmed MET collection if the option is set to false
usePrivateSQlite = options.usePrivateSQLite #use external JECs (sqlite file)
applyResiduals   = options.isData           #application of residual corrections. 
                                            #   Have to be set to True once the 13 TeV residual corrections are available. 
                                            #   False to be kept meanwhile. Can be kept to False later for private tests
                                            #   or for analysis checks and developments (not the official recommendation!).
if not (options.forceResiduals == None):
   applyResiduals = (options.forceResiduals == True)

#------------------------------------------------------------------------------- 
#   Setting up process
#------------------------------------------------------------------------------- 
process = cms.Process("ggChannelFilter")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.categories.append('HLTrigReport')
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvts) )

process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring(options.sample)
      )

                                                                                                                                          #process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")

if options.globalTag == "":
   if options.DataProcessing=="MC50ns":
      process.GlobalTag.globaltag="MCRUN2_74_V9A"
   elif options.DataProcessing=="MC25ns":
      process.GlobalTag.globaltag="MCRUN2_74_V9"
   elif options.DataProcessing=="Data50ns":
      process.GlobalTag.globaltag="74X_dataRun2_Prompt_v0"
   elif options.DataProcessing=="Data25ns":
      process.GlobalTag.globaltag="74X_dataRun2_Prompt_v1"
   else:
      print "Choose any of the following options for 'DataProcessing'", "MC50ns,  MC25ns, Data50ns, Data25ns" 
else: 
   print "You have chosen globalTag as", options.globalTag, ". Please check if this corresponds to your dataset."
process.GlobalTag.globaltag = options.globalTag 


process.TFileService = cms.Service("TFileService",
          fileName = cms.string( options.outputLabel )
          )
process.filterAnalyzer = cms.EDAnalyzer(
      "filterAnalyzer",
      muonsrc     = cms.InputTag( "slimmedMuons" ) ,
      elecsrc     = cms.InputTag( "slimmedElectrons" ),
      jetsrc      = cms.InputTag( "slimmedJets" ),
      metsrc      = cms.InputTag( "slimmedMETs" ) ,
      vertexsrc   = cms.InputTag( "offlineSlimmedPrimaryVertices" ),
      convsrc     = cms.InputTag("reducedEgamma","reducedConversions"),
      rhosrc      = cms.InputTag( "fixedGridRhoFastjetAll" ),
      beamspotsrc = cms.InputTag( "offlineBeamSpot" )
      )

process.outpath = cms.EndPath(
      process.filterAnalyzer
      )
