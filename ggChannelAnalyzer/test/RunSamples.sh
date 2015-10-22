#-------------------------------------------------------------------------------
#
#   File        : RunSamples.sh
#   Descriptions: Running over filtered miniAOD samples
#   Usage       : ./RunSamples.sh
#
#-------------------------------------------------------------------------------
#!/bin/bash

cmsRun analyzer_cfg.py DataProcessing=Data25ns sample=file:///wk_cms/yichen/ggChannel_tuples/SingleElectron_Run2015D-05Oct2015-v1/miniAOD.root filename=SingleElectron.root
cmsRun analyzer_cfg.py DataProcessing=Data25ns sample=file:///wk_cms/yichen/ggChannel_tuples/SingleMuon_Run2015D-05Oct2015-v1/miniAOD.root filename=SingleMuon.root 

cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=TTJets.root 

cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root  filename=ST_s-channel.root

cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=ST_t-channel_antitop.root 

cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=ST_t-channel-top.root 

cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/ST_tW_antitop_5f_DS_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=ST_tW_antitop.root

cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/ST_tW_top_5f_DS_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filname=ST_tW_top.root

cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M1000.root 
cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M900.root 
cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M800.root 
cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M700.root 
cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M1100.root 
cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M1200.root 
cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M1300.root 
cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M1400.root 
cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M1500.root 
cmsRun analyzer_cfg.py sample=file:///wk_cms/yichen/ggChannel_tuples/TstarTstarToTgluonTgluon_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/miniAOD.root filename=Tstar_M1600.root 





