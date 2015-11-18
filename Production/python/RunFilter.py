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

myOptions.obj.register( "filterType",
      "gg_MuonSignal",
      opts.VarParsing.multiplicity.singleton,
      opts.VarParsing.varType.string,
      "Type of filter to run" )

print( "Begin parsing inputs" )
myOptions.obj.parseArguments()

process = cms.Process( "ggFilter" )
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
         "keep *",
         )
      )

#------------------------------------------------------------------------------- 
#   EDFilter settings
#------------------------------------------------------------------------------- 
process.TFileService = cms.Service("TFileService",
      fileName = cms.string( myOptions.obj.histFile )
      )

process.filterType = cms.EDFilter(
      myOptions.obj.filterType ,
      eleLooseIdMap   = cms.InputTag( elec_loose_id_label  ) ,
      eleMediumIdMap  = cms.InputTag( elec_medium_id_label ) ,
      )

process.p1 = cms.Path(
      process.egmGsfElectronIDSequence * 
      process.filterType
      )

process.outpath = cms.EndPath(
      process.out
      )

