include ../Makefile.rules

BINARY = sapTest

HDRS = sapTest.h
SRCS = sapTest.cpp
OBJS = sapTest.o

DEPLIBS = ../Altova/libAltova.a ../AltovaXML/libAltovaXML.a ../sap/libsap.a
SHAREDDEPLIBS = ../Altova/libAltova.so ../AltovaXML/libAltovaXML.so ../sap/libsap.so
LINKLIBS = sap -lAltovaXML -lAltova -lxerces-c
LINKDIRS = ../Altova -L../AltovaXML -L../sap -L/data/SAPDEV/lib
Q ?= @

.PHONY: all clean

all: $(BINARY)

$(DEPLIBS):
	cd .. && $(MAKE)
	
$(SHAREDDEPLIBS):
	cd .. && $(MAKE)
	

$(BINARY): $(OBJS) $(SHAREDDEPLIBS)

	@echo '===> LINKING $@'
	$(Q)$(CXX) -fPIC $(BINARY).o -o $(BINARY) -L$(LINKDIRS) -l$(LINKLIBS)
	$(Q)chmod 755 run.sh

$(OBJS): $(SRCS) $(HDRS)

clean:
	rm -Rf $(BINARY) $(OBJS)
