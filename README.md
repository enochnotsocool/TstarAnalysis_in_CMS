# Tstar Analysis in CMS Software

Analysis code for the search for excited top quark. Attempts to stripped desired events 
into simple root formats for multiple channel analysis

## Requirements 

  * [MiniAODAnalysis/BaseFilter](https://github.com/enochnotsocool/MiniAODAnalysis.git)
  * [MiniAODAnalysis/BaseAnalyzer](https://github.com/enochnotsocool/MiniAODAnalysis)
  * [bpkFrameWork/ModifiedHitFit](https://github.com/ntuhep/ModifiedHitFit)


## Deployment commands
```
cmsrel CMSSW_7_4_15_patch1
cd CMSSW_7_4_15_patch1/src/
cmsenv

git cms-merge-topic ikrav:egm_id_7.4.12_v1
git clone https://github.com/ntuhep/ModifiedHitFit.git bpkFrameWork/ModifiedHitFit
git clone https://github.com/enochnotsocool/MiniAODAnalysis.git
git clone https://github.com/enochnotsocool/TstarAnalysis_in_CMS.git TstarAnalysis
scram b -j 8
```

