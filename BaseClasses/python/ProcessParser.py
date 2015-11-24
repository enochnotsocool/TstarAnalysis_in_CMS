##**************************************************************************************************
##
##    FileName   :  DataProcessParser.py
##    Description:  Common functions for data processing parsing 
##
##**************************************************************************************************
import sys

#------------------------------------------------------------------------------- 
#   Global tags for Run II
#   https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD
#------------------------------------------------------------------------------- 
def getGlobalTag( dataProcess ):
   if dataProcess == "MC25ns_MiniAODv2":
      return "74X_mcRun2_asymptotic_v2"
   elif dataProcess =="MC25ns_MiniAODv2_FastSim":
      return "74X_mcRun2_asymptotic_v2"
   elif dataProcess=="Data25ns_ReReco":
      return "74X_dataRun2_v4"
   elif dataProcess=="Data25ns_MiniAODv2":
      return "74X_dataRun2_reMiniAOD_v0"
   elif dataProcess=="Data25ns_PromptRecov4":
      return "74X_dataRun2_Prompt_v4"
   elif dataProcess=="MC50ns_MiniAODv2":
      return "74X_mcRun2_asymptotic50ns_v0"
   elif dataProcess=="Data50ns_MiniAODv2":
      return "74X_dataRun2_reMiniAOD_v0"
   else:
      print "Wrong input!!!"
      print dataProcess 
      sys.exit("!!!!Error: Wrong DataProcessing option. Choose any of the following options: "
            "'MC25ns_MiniAODv2', 'MC25ns_MiniAODv2_FastSim', 'Data25ns_ReReco', 'Data25ns_MiniAODv2', 'Data25ns_PromptRecov4',\n"
            "'MC50ns_MiniAODv2', 'Data50ns_MiniAODv2'\n")

#------------------------------------------------------------------------------- 
#   Electron ID tags for Run II
#   https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2 
#------------------------------------------------------------------------------- 
def getElectronIDLabel( workingPoint , processType ):
   if ( "50ns" in processType ):
      if workingPoint == "veto" :
         return "egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-veto"
      elif workingPoint == "loose" :
         return "egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-loose"
      elif workingPoint == "medium" :
         return "egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-medium"
      elif workingPoint == "tight" :
         return "egmGsfElectronIDs:cutBasedElectronID-Spring15-50ns-V2-standalone-tight"
      else :
         return ""

   elif ( "25ns" in processType ):
      if workingPoint == "veto" :
         return "egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-veto"
      elif workingPoint == "loose" :
         return "egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-loose"
      elif workingPoint == "medium" :
         return "egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-medium"
      elif workingPoint == "tight" :
         return "egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight"
      else :
         return ""

   else :
      return ""

def getElectronIDModule( processType ):
   if "50ns" in processType :
      return "RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_50ns_V2_cff"

   elif "25ns" in processType :
      return "RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff"

   else :
      return ""
