SampleInfo.d: ../../include/SampleDef.h ../../include/SampleInfo.h 
../../include/SampleDef.h: SampleDef.h
	@rm -f ../../include/SampleDef.h
	@ln -fs ../src/SampleInfo/SampleDef.h ../../include/SampleDef.h
../../include/SampleInfo.h: SampleInfo.h
	@rm -f ../../include/SampleInfo.h
	@ln -fs ../src/SampleInfo/SampleInfo.h ../../include/SampleInfo.h
