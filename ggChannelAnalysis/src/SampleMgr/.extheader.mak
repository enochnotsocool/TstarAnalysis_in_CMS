SampleMgr.d: ../../include/SampleMgr.h 
../../include/SampleMgr.h: SampleMgr.h
	@rm -f ../../include/SampleMgr.h
	@ln -fs ../src/SampleMgr/SampleMgr.h ../../include/SampleMgr.h
