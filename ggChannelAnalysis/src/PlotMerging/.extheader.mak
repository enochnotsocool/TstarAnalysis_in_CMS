PlotMerging.d: ../../include/PlotMerging.h 
../../include/PlotMerging.h: PlotMerging.h
	@rm -f ../../include/PlotMerging.h
	@ln -fs ../src/PlotMerging/PlotMerging.h ../../include/PlotMerging.h
