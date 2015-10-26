SampleInfo.d: ../../include/SampleInfo.h 
../../include/SampleInfo.h: SampleInfo.h
	@rm -f ../../include/SampleInfo.h
	@ln -fs ../src/SampleInfo/SampleInfo.h ../../include/SampleInfo.h
