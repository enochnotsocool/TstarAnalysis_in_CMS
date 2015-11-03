InitBase output_ElectronSignal.root
SetLumi 573.8
Dofile  ./dofiles/ElectronSignal/Data.do
Dofile  ./dofiles/ElectronSignal/TTJets.do
Dofile  ./dofiles/ElectronSignal/SingleTop.do
Dofile  ./dofiles/ElectronSignal/Tstar.do
SetSignal Tstar_M1000
Dofile  ./dofiles/makePlots.do
print
Clear
Quit -f 

