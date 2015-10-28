PlotCmd.d: ../../include/plotCmd.h 
../../include/plotCmd.h: plotCmd.h
	@rm -f ../../include/plotCmd.h
	@ln -fs ../src/PlotCmd/plotCmd.h ../../include/plotCmd.h
