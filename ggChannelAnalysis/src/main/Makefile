PKGFLAG   =
EXTHDRS   = 

include ../Makefile.in

BINDIR    = ../../bin
TARGET    = $(BINDIR)/$(EXEC)

target: $(TARGET)

$(TARGET): $(COBJS) $(LIBDEPEND)
	@echo "> building $(EXEC)..."
	@$(CXX) $(CFLAGS) -L$(LIBDIR) $(DEPENDDIR) $(COBJS)  $(INCLIB) -o $(TARGET)

