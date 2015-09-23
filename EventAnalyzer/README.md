# Event Analyzer

This is a CMSSW EDAnalyzer inheritance classed used for event selection and early stage computations.
Note that the selection criteria is the same as the ones used in this i
[analysis note](http://cms.cern.ch/iCMS/analysisadmin/cadilines?line=B2G-12-014&tp=an&id=954&ancode=B2G-12-014)

The below is a quick overview of the algorithm used for the event selection:

1. Get primary vertex
2. Get "Loose" and "Tight" Muons
3. Get "Loose" and "Tight" Electrons
4. Get "Loose" Jets
5. See if event passes object selection criteria, 
   if yes, then store required objects only( "Tight" Muons, "Tight electrons", "Loose Jets", MET, Primary Vertex )
   Note that objects will be store in standard CMSSW formats.


## Muon selection
The muon selection requires the 
[relative combined particle flow isolation variable](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Muon_Isolation).
( Note: requires update in RunII )
### Loose muons:
  * Standard [loose muon](https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Loose_Muon)
  * $p_t > 10$
  * $\left| \eta eta \right| < 2.5 $
  * $pfIso < 0.2 $

### Tight muon:
  * Standard [tight muon](https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Tight_Muon)
  * $p_t > 26$
  * $\left| eta \right| < 2.1$
  * $pfIso < 0.12$


## Electron selection
The electron selection requires the [relative combined particle flow isolation variable](https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPFBasedIsolationRun2)( Note: this is updated for RunII )

### Loose electrons:
  * $p_t > 20 $
  * $\left| \eta \right| < 2.5 $
  * MVA identification variables $ > 0 $ ( Not updated for RunII ) 
  * $ pfIso < 0.15 $
### Tight electron:
  * $p_t > 30 $
  * $ \left| \eta \right| < 1.5 $
  * MVA identification variables $> 0.5 $ 
  * $ pfIso < 0.1 $
  * no conversion photon (NOT FOUND!)
  * GSF tracks impact parameter $d_{xy} < 0.2 $

## Jet Selection
  * $p_t > 30 $
  * $\left| \eta \right| < 2.5 $
  * [Standard Loose Jet ID](https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_13_TeV_data)
  * $\Delta R > 0.5$ against primary tight electron
b jets require a CSV discriminant variable $> 0.679$



# Event selection 
  * Exactly one tight lepton (muon or electron)
  * No additional Loose leptons.
  * $>=6$ Loose jets
  * $>=1$ b-tagged loose jet.
