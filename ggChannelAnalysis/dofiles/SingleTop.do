AddType      SingleTop_Schannel
AddFile      SingleTop_Schannel  ./sample/ST_s-channel.root
SetXSection  SingleTop_Schannel  14.4
SetEff       SingleTop_Schannel  0.000600

AddType      SingleTop_Tchannel_top
AddFile      SingleTop_Tchannel_top  ./sample/ST_t-channel_top.root
SetXSection  SingleTop_Tchannel_top  136.02
SetEff       SingleTop_Tchannel_top  0.000722

AddType      SingleTop_Tchannel_antitop 
AddFile      SingleTop_Tchannel_antitop  ./sample/ST_t-channel_antitop.root
SetXSection  SingleTop_Tchannel_antitop  80.95
SetEff       SingleTop_Tchannel_antitop  0.000722

AddType      SingleTop_TWchannel_top
AddFile      SingleTop_TWchannel_top  ./sample/ST_tW_top.root
SetXSection  SingleTop_TWchannel_top  35.6
SetEff       SingleTop_TWchannel_top  0.001378

AddType      SingleTop_TWchannel_antitop
AddFile      SingleTop_TWchannel_antitop  ./sample/ST_tW_antitop.root
SetXSection  SingleTop_TWchannel_antitop  35.6
SetEff       SingleTop_TWchannel_antitop  0.001414

