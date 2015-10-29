AnalysisMgr.d: ../../include/AnalysisMgr.h 
../../include/AnalysisMgr.h: AnalysisMgr.h
	@rm -f ../../include/AnalysisMgr.h
	@ln -fs ../src/AnalysisMgr/AnalysisMgr.h ../../include/AnalysisMgr.h
