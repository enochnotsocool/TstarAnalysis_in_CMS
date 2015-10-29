AnaCmd.d: ../../include/AnaCmd.h 
../../include/AnaCmd.h: AnaCmd.h
	@rm -f ../../include/AnaCmd.h
	@ln -fs ../src/AnaCmd/AnaCmd.h ../../include/AnaCmd.h
