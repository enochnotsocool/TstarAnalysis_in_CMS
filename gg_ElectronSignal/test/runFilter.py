import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts
import TstarAnalysis.BaseClasses.ProcessParser as myParser
import TstarAnalysis.BaseClasses.CommonOptions as myOptions
import TstarAnalysis.BaseClasses.CommonProcess as myProcess 
import copy

myOptions.initOptions( 'analysis' )

print( "Adding additional option settings" )
myOptions.obj.register("histFile",
      "myHist.root",
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      'Histogram filename')

print( "Begin parsing inputs" )
myOptions.obj.parseArguments()

process = cms.Process( "ggElectronSignal" )
myProcess.initProcess( process )

#------------------------------------------------------------------------------- 
#   Egamma ID pre-requisites
#-------------------------------------------------------------------------------
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer( process,  dataFormat )

my_elid_modules      = myParser.getElectronIDModule( myOptions.obj.DataProcessing );
elec_loose_id_label  = myParser.getElectronIDLabel( "loose"  , myOptions.obj.DataProcessing );
elec_medium_id_label = myParser.getElectronIDLabel( "medium" , myOptions.obj.DataProcessing );

setupAllVIDIdsInModule( process , my_elid_modules ,setupVIDElectronSelection)

#------------------------------------------------------------------------------- 
#   Output Modules settings
#------------------------------------------------------------------------------- 
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning
process.out = cms.OutputModule(
      "PoolOutputModule",
      fileName = cms.untracked.string( myOptions.obj.outputLabel ),
      SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
      outputCommands = cms.untracked.vstring(
         "drop *",
         "keep *_TriggerResults_*_*",
         "keep *_fixedGridRhoFastjetAll_*_*",
         "keep *_offlineSlimmedPrimaryVertices_*_*",
         "keep *_slimmedAddPileupInfo_*_*",
         "keep *_slimmedMETs_*_*",
         "keep *_slimmedMuons_*_*",
         "keep *_slimmedElectrons_*_*",
         "keep *_slimmedJets_*_*",
         "keep *_reducedEgamma_*_*",
         "keep *_offlineBeamSpot_*_*",
         "keep *_addPileupInfo_*_*"
         )
      )

#------------------------------------------------------------------------------- 
#   EDFilter settings
#------------------------------------------------------------------------------- 
process.TFileService = cms.Service("TFileService",
      fileName = cms.string( myOptions.obj.histFile )
      )

process.gg_ElectronSignal = cms.EDFilter(
      "gg_ElectronSignal",
      hltsrc      = cms.untracked.InputTag("TriggerResults::HLT"),
      metsrc      = cms.untracked.InputTag( "slimmedMETs" ) ,
      pileupsrc   = cms.untracked.InputTag( "slimmedAddPileupInfo" ),
      vertexsrc   = cms.untracked.InputTag( "offlineSlimmedPrimaryVertices" ),
      convsrc     = cms.untracked.InputTag( "reducedEgamma","reducedConversions"),
      rhosrc      = cms.untracked.InputTag( "fixedGridRhoFastjetAll" ),
      beamspotsrc = cms.untracked.InputTag( "offlineBeamSpot" ),
      muonsrc     = cms.untracked.InputTag( "slimmedMuons" ) ,
      elecsrc     = cms.untracked.InputTag( "slimmedElectrons" ),
      jetsrc      = cms.untracked.InputTag( "slimmedJets" ),
      eleLooseIdMap   = cms.InputTag( elec_loose_id_label  ) ,
      eleMediumIdMap  = cms.InputTag( elec_medium_id_label ) ,
      )

process.p1 = cms.Path(
      process.egmGsfElectronIDSequence * 
      process.gg_ElectronSignal
      )

process.outpath = cms.EndPath(
      process.out
      )
