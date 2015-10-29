InitBase ntuplizer/TstarAnalysis
SetLumi 531.8
Dofile  ./dofiles/TTJets.do
Dofile  ./dofiles/SingleTop.do
Dofile  ./dofiles/Data.do 
MakeBasic
MakeCombine  ChiSquareMass
ClearPlot
q -f 


