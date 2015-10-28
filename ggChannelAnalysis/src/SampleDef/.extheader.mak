SampleDef.d: ../../include/NumDef.h ../../include/SampleDef.h 
../../include/NumDef.h: NumDef.h
	@rm -f ../../include/NumDef.h
	@ln -fs ../src/SampleDef/NumDef.h ../../include/NumDef.h
../../include/SampleDef.h: SampleDef.h
	@rm -f ../../include/SampleDef.h
	@ln -fs ../src/SampleDef/SampleDef.h ../../include/SampleDef.h
