SampleDef.d: ../../include/SampleDef.h 
../../include/SampleDef.h: SampleDef.h
	@rm -f ../../include/SampleDef.h
	@ln -fs ../src/SampleDef/SampleDef.h ../../include/SampleDef.h
