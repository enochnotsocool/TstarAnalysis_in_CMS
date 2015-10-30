AddType      SingleTop_Schannel
AddFile      SingleTop_Schannel  ./sample/MuonSignal/ST_s-channel.root
SetXSection  SingleTop_Schannel  14.4
SetEff       SingleTop_Schannel  0.000101584722
SetColor     SingleTop_Schannel  cyan

AddType      SingleTop_Tchannel_top
AddFile      SingleTop_Tchannel_top  ./sample/MuonSignal/ST_t-channel_top.root
SetXSection  SingleTop_Tchannel_top  136.02
SetEff       SingleTop_Tchannel_top  0.000153233221
SetColor     SingleTop_Tchannel_top  cyan

AddType      SingleTop_Tchannel_antitop 
AddFile      SingleTop_Tchannel_antitop  ./sample/MuonSignal/ST_t-channel_antitop.root
SetXSection  SingleTop_Tchannel_antitop  80.95
SetEff       SingleTop_Tchannel_antitop  0.000115763362
SetColor     SingleTop_Tchannel_antitop  cyan

AddType      SingleTop_TWchannel_top
AddFile      SingleTop_TWchannel_top  ./sample/MuonSignal/ST_tW_top.root
SetXSection  SingleTop_TWchannel_top  35.6
SetEff       SingleTop_TWchannel_top  0.000153233221
SetColor     SingleTop_TWchannel_top  cyan

AddType      SingleTop_TWchannel_antitop
AddFile      SingleTop_TWchannel_antitop  ./sample/MuonSignal/ST_tW_antitop.root
SetXSection  SingleTop_TWchannel_antitop  35.6
SetEff       SingleTop_TWchannel_antitop  0.000242000000
SetColor     SingleTop_TWchannel_antitop  cyan

