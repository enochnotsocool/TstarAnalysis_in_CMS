InitBase ntuplizer/TstarAnalysis
SetLumi 573.8
Dofile  ./dofiles/ElectronSignal/Data.do
Dofile  ./dofiles/ElectronSignal/TTJets.do
Dofile  ./dofiles/ElectronSignal/SingleTop.do
Dofile  ./dofiles/ElectronSignal/Tstar.do
MakeBasic
MakeCombine  ChiSquareMass
MakeCombine  JetPt
MakeCombine  LeptonPt
print
Clear
Quit -f 

