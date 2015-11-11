#**************************************************************************************************
#
#    FileName   :  CommonOptions.py
#    Description:  Initializing common functions
#
#**************************************************************************************************
import FWCore.ParameterSet.VarParsing as opts

def initOptions( name ):
   global obj 
   print( "Setting up common options parameters" )
   obj = opts.VarParsing ( name )
   
   #----- Common input functions for testing  -----------------------------------------------------
   obj.setDefault( "maxEvents" , 10000 );

   obj.register('sample',
         'file:///wk_cms/yichen/miniAODs/MC_reMiniAOD_25ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root',
         opts.VarParsing.multiplicity.list,
         opts.VarParsing.varType.string,
         'Sample to analyze')
   
   obj.register('DataProcessing',
         "MC25ns",
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.string,
         'Data processing type')

   obj.register('jsonFile',
         '',
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.string,
         "Golden Json file input" )

   obj.register('outputLabel',
         'myOutput.root',
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.string,
         'Output label')
   
   obj.register('Debug',
         0,
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.int,
         'Debugging output level' )

   #----- B2G Group recommendations --------------------------------------------------------------------
   obj.register('useNoHFMET',
         True,
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.bool,
         'Adding met without HF and relative jets')

   obj.register('usePrivateSQLite',
         True,
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.bool,
         'Take Corrections from private SQL file')

   obj.register('forceResiduals',
         None,
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.bool,
         'Whether to force residuals to be applied')


