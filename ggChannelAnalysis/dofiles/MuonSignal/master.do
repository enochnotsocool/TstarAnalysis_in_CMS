InitBase output_MuonSignal.root
SetLumi 573.8
Dofile  ./dofiles/MuonSignal/Data.do
Dofile  ./dofiles/MuonSignal/TTJets.do
Dofile  ./dofiles/MuonSignal/SingleTop.do
Dofile  ./dofiles/MuonSignal/Tstar.do
SetSignal Tstar_M1000
Dofile  ./dofiles/makePlots.do
print
Clear
Quit -f 

