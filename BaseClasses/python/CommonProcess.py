##**************************************************************************************************
##
##    FileName   :  Commonobj.py
##    Description:  Loading common obj settings
##**************************************************************************************************
import TstarAnalysis.BaseClasses.CommonOptions as myOptions 
import TstarAnalysis.BaseClasses.ProcessParser as myParser
import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList

def initProcess( obj ):
   print( "Loading common Process parameters" )
   obj.load("FWCore.MessageService.MessageLogger_cfi")
   obj.MessageLogger.cerr.FwkReport.reportEvery = 10000
   obj.MessageLogger.categories.append('HLTrigReport')

   obj.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
   obj.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( myOptions.obj.maxEvents ) )
   obj.source    = cms.Source("PoolSource", fileNames = cms.untracked.vstring( myOptions.obj.sample ) )
   obj.source.lumisToProcess = LumiList.LumiList(filename = myOptions.obj.jsonFile ).getVLuminosityBlockRange()

   #obj.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
   obj.load("Configuration.EventContent.EventContent_cff")
   obj.load('Configuration.StandardSequences.GeometryDB_cff')
   obj.load('Configuration.StandardSequences.MagneticField_38T_cff')
   obj.load('Configuration.StandardSequences.Services_cff')
   obj.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
   obj.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")

   obj.GlobalTag.globaltag = myParser.getGlobalTag( myOptions.obj.DataProcessing );

