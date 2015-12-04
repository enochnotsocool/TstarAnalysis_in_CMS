#**************************************************************************************************
#
#    FileName   :  CommonOptions.py
#    Description:  Initializing common functions
#
#**************************************************************************************************
import FWCore.ParameterSet.VarParsing as opts

def initOptions( options ):
   print( "Setting up common options parameters" )
   
   #----- Common input functions for testing  -----------------------------------------------------
   options.setDefault( "maxEvents" , 10000 );

   options.register('sample',
         '',
         opts.VarParsing.multiplicity.list,
         opts.VarParsing.varType.string,
         'Sample to analyze')
   
   options.register('DataProcessing',
         '',
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.string,
         'Data processing type')

   options.register('jsonFile',
         '',
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.string,
         "Golden Json file input" )

   options.register('outputLabel',
         'myOutput.root',
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.string,
         'Output label')
   
   options.register('Debug',
         0,
         opts.VarParsing.multiplicity.singleton,
         opts.VarParsing.varType.int,
         'Debugging output level' )

   #----- B2G Group recommendations --------------------------------------------------------------------
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


