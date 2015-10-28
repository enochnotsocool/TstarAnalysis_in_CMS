REFPKGS = cmd
SRCPKGS = util PlotCmd PlotMerging SampleInfo RootFormat SampleDef 
LIBPKGS = $(REFPKGS) $(SRCPKGS)
MAIN    = main 

LIBS     = $(addprefix -l, $(LIBPKGS))
SRCLIBS  = $(addsuffix .a, $(addprefix lib, $(SRCPKGS)))

EXEC    = ggChannelAnalysis.out 

all: libs main 

libs:
	@for pkg in $(SRCPKGS) ; do \
		echo "Checking $$pkg..."; \
		cd src/$$pkg; make --no-print-directory PKGNAME=$$pkg; \
		cd ../..; \
	done 

main:
	@echo "Checking $(MAIN)..."
	@cd src/$(MAIN); \
		make --no-print-directory INCLIB="$(LIBS)" EXEC=$(EXEC);

clean:
	@for pkg in $(SRCPKGS); \
		do \
		echo "Cleaning $$pkg..."; \
		cd src/$$pkg; make --no-print-directory PKGNAME=$$pkg clean; \
		cd ../..; \
		done
	@echo "Cleaning $(MAIN)..."
	@cd src/$(MAIN); make --no-print-directory clean
	@echo "Removing $(SRCLIBS)..."
	@cd lib; rm -f $(SRCLIBS)
	@echo "Removing object files..."

