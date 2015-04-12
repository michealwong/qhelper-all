include ../Makefile.rules

NAME = sap
DEPLIBS = ../Altova/libAltova.a ../AltovaXML/libAltovaXML.a
SHAREDDEPLIBS = ../Altova/libAltova.so ../AltovaXML/libAltovaXML.so
LIB = lib$(NAME).a
SHAREDLIB = lib$(NAME).so

HDRS = sap-typeinfo.h
HDRS +=	sap.h

HDRS += type_.Csap.h
HDRS += type_.CsaprootType.h
HDRS += type_.CresultType.h
HDRS += type_.CdataheadType.h
HDRS += type_.CresultsetType.h
HDRS += type_.CitemsType.h
HDRS += type_xs.CENTITIES.h
HDRS += type_xs.CENTITY.h
HDRS += type_xs.CID.h
HDRS += type_xs.CIDREF.h
HDRS += type_xs.CIDREFS.h
HDRS += type_xs.CNCName.h
HDRS += type_xs.CNMTOKEN.h
HDRS += type_xs.CNMTOKENS.h
HDRS += type_xs.CNOTATION.h
HDRS += type_xs.CName.h
HDRS += type_xs.CQName.h
HDRS += type_xs.CanySimpleType.h
HDRS += type_xs.CanyType.h
HDRS += type_xs.CanyURI.h
HDRS += type_xs.Cbase64Binary.h
HDRS += type_xs.Cboolean.h
HDRS += type_xs.Cbyte.h
HDRS += type_xs.Cdate.h
HDRS += type_xs.CdateTime.h
HDRS += type_xs.Cdecimal.h
HDRS += type_xs.Cdouble.h
HDRS += type_xs.Cduration.h
HDRS += type_xs.Cfloat.h
HDRS += type_xs.CgDay.h
HDRS += type_xs.CgMonth.h
HDRS += type_xs.CgMonthDay.h
HDRS += type_xs.CgYear.h
HDRS += type_xs.CgYearMonth.h
HDRS += type_xs.ChexBinary.h
HDRS += type_xs.Cinteger.h
HDRS += type_xs.Clanguage.h
HDRS += type_xs.Clong.h
HDRS += type_xs.CnegativeInteger.h
HDRS += type_xs.CnonNegativeInteger.h
HDRS += type_xs.CnonPositiveInteger.h
HDRS += type_xs.CnormalizedString.h
HDRS += type_xs.CpositiveInteger.h
HDRS += type_xs.Cshort.h
HDRS += type_xs.Ctime.h
HDRS += type_xs.Ctoken.h
HDRS += type_xs.CunsignedByte.h
HDRS += type_xs.CunsignedInt.h
HDRS += type_xs.CunsignedLong.h
HDRS += type_xs.CunsignedShort.h
HDRS += type_xs.CintType.h
HDRS += type_xs.CstringType.h


SRCS = sap.cpp sap-typeinfo.cpp

OBJS = $(filter %.o, $(SRCS:.cpp=.o))
Q ?= @

.PHONY: all clean


all: $(SHAREDLIB)


$(SHAREDLIB): $(OBJS) $(SHAREDDEPLIBS)
	@echo '===> Linking shared $(SHAREDLIB)'
	$(Q)gcc -shared -Wl,-soname,$(SHAREDLIB) -o $(SHAREDLIB)$(VERSION) $(OBJS)
	$(Q)ln -s $(SHAREDLIB)$(VERSION) $(SHAREDLIB)
	cp $(SHAREDLIB) ../../../lib

$(LIB): $(OBJS) $(DEPLIBS)
	@echo '===> Linking $(LIB)'
	$(Q)ar cr $(LIB) $(OBJS)
	$(Q)ranlib $(LIB)
	cp $(LIB) ../../../lib

$(OBJS): $(HDRS) $(SRCS)

clean:
	rm -Rf $(OBJS) $(LIB) $(SHAREDLIB)
