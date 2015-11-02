InitBase output_MuonSignal.root
SetLumi 573.8
Dofile  ./dofiles/MuonSignal/Data.do
Dofile  ./dofiles/MuonSignal/TTJets.do
Dofile  ./dofiles/MuonSignal/SingleTop.do
Dofile  ./dofiles/MuonSignal/Tstar.do
SetSignal Tstar_M1000
MakeBasic
MakeCombine  ChiSquareMass
MakeCombine  JetPt
MakeCombine  LeptonPt
print
Clear
Quit -f 

