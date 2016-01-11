# Tstar Analysis in CMS Software

Analysis code for the search for excited top quark. Attempts to stripped desired events 
into simple root formats for multiple channel analysis

## Requirements 

  * [bpkFrameWork/ModifiedHitFit](https://github.com/ntuhep/ModifiedHitFit)


## Deployment commands
```
cmsrel CMSSW_7_4_15_patch1
cd CMSSW_7_4_15_patch1/src/
cmsenv

git cms-merge-topic ikrav:egm_id_7.4.12_v1

git clone https://github.com/ntuhep/bpkFrameWork.git
cd bpkFrameWork 
git submodule init ModifiedHitFit 
git submodule update
cd ../

git clone https://github.com/enochnotsocool/TstarAnalysis_in_CMS.git TstarAnalysis
scram b -j 8
```

## Running an analysis from data to results

### The filter classes 
Navigate to the `Filters/test` directory from there you could make your own filtered MiniAOD files

### The Ntuplizer
Navigate to the `ggChannel_Ntuplizer/test`  directory, and you could make a minimal analysis file based on the filtered MiniAOD files

### The CombineAnalysis
Navigate to the `CombineAnalysis/` directory, the `./RunMuon.out` executable reads file in `CombineAnalysis/data` to generate the analysis results


