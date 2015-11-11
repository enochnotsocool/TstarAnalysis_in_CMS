##**************************************************************************************************
##
##    FileName   :  DataProcessParser.py
##    Description:  Common functions for data processing parsing 
##
##**************************************************************************************************


#------------------------------------------------------------------------------- 
#   Global tags for Run II
#   https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD
#------------------------------------------------------------------------------- 
def getGlobalTag( x ):
   if x == "MC50ns":
      return "74X_mcRun2_asymptotic50ns_v0"
   elif x == "MC25ns":
      return "74X_mcRun2_asymptotic_v2"
   elif x == "Data50ns":
      return "74X_dataRun2_reMiniAOD_v0"
   elif x == "DataRunC25ns":
      return "74X_dataRun2_v4"
   elif x == "DataRunD_PromptReco" :
      return "74X_dataRun2_Prompt_v4"
   elif x == "DataRunD_re" :
      return "74X_dataRun2_reMiniAOD_v0"
   else:
      return ""

#------------------------------------------------------------------------------- 
#   Electron ID tags for Run II
#   https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2 
#------------------------------------------------------------------------------- 
def getElectronIDLabel( workingPoint , processType ):
   if ( processType == "MC50ns" or processType == "Data50ns" ):
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
 
   elif ( processType == "MC25ns" or processType == "DataRunC25ns" 
         or processType== "DataRunD_PromptReco" or processType == "DataRunD_re" ):
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
   if ( processType == "MC50ns" or processType == "Data50ns" ):
      return "RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_50ns_V2_cff"
 
   elif ( processType == "MC25ns" or processType == "DataRunC25ns" 
         or processType== "DataRunD_PromptReco" or processType == "DataRunD_re" ):
      return "RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff"

   else :
      return ""
