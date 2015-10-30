InitBase ntuplizer/TstarAnalysis
SetLumi 573.8
Dofile  ./dofiles/MuonSignal/Data.do
Dofile  ./dofiles/MuonSignal/TTJets.do
Dofile  ./dofiles/MuonSignal/SingleTop.do
Dofile  ./dofiles/MuonSignal/Tstar.do
MakeBasic
MakeCombine  ChiSquareMass
MakeCombine  JetPt
MakeCombine  LeptonPt
print
Clear
Quit -f 

