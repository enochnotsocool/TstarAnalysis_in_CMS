PlotDef.d: ../../include/PlotDef.h 
../../include/PlotDef.h: PlotDef.h
	@rm -f ../../include/PlotDef.h
	@ln -fs ../src/PlotDef/PlotDef.h ../../include/PlotDef.h
