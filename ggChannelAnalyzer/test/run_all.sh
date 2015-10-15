#!/bin/bash

MC_BASE="file:///wk_cms/yichen/ggChannel_tuples/mc/"
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root filename="Tstar-M1000.root" maxEvts=-1
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root filename="Tstar-M1100.root" maxEvts=-1 
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root filename="Tstar-M1200.root" maxEvts=-1 
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root filename="Tstar-M1300.root" maxEvts=-1 
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root filename="Tstar-M1400.root" maxEvts=-1 
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root filename="Tstar-M1500.root" maxEvts=-1 
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root filename="Tstar-M1600.root" maxEvts=-1 
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root  filename="Tstar-M900.root" maxEvts=-1  
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root  filename="Tstar-M800.root" maxEvts=-1  
cmsRun analyzer_cfg.py sample=$MC_BASE/TstarTstarToTgluonTgluon_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8/miniAOD.root  filename="Tstar-M700.root" maxEvts=-1  

cmsRun analyzer_cfg.py sample=$MC_BASE/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/miniAOD.root                          filename="TTJets.root" maxEvts=-1
cmsRun analyzer_cfg.py sample=$MC_BASE/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/miniAOD.root       filename="SingleTop_sChannel.root" maxEvts=-1
cmsRun analyzer_cfg.py sample=$MC_BASE/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/miniAOD.root filename="SingleTop_tChannel_t.root" maxEvts=-1
cmsRun analyzer_cfg.py sample=$MC_BASE/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/miniAOD.root     filename="SingleTop_tChannel_tbar.root" maxEvts=-1
cmsRun analyzer_cfg.py sample=$MC_BASE/ST_tW_antitop_5f_DS_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/miniAOD.root  filename="SingleTop_tW_t.root" maxEvts=-1
cmsRun analyzer_cfg.py sample=$MC_BASE/ST_tW_top_5f_DS_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/miniAOD.root      filename="SingleTop_tW_tbar.root" maxEvts=-1
