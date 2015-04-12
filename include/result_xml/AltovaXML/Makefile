include ../Makefile.rules

NAME = AltovaXML
LIB = lib$(NAME).a
SHAREDLIB = lib$(NAME).so

HDRS =  AltovaXMLAPI.h
HDRS += XmlException.h
HDRS += Node.h
HDRS += XercesString.h

SRCS = XmlException.cpp Node.cpp



OBJS = $(filter %.o, $(SRCS:.cpp=.o))
Q ?= @

.PHONY: all clean


all: $(SHAREDLIB)


$(SHAREDLIB): $(OBJS)
	@echo '===> Linking shared $(SHAREDLIB)'
	$(Q)gcc -shared -Wl,-soname,$(SHAREDLIB) -o $(SHAREDLIB)$(VERSION) $(OBJS) 
	$(Q)ln -s $(SHAREDLIB)$(VERSION) $(SHAREDLIB)
	cp $(SHAREDLIB) ../../../lib

$(LIB): $(OBJS)
	@echo '===> Linking $(LIB)'
	$(Q)ar cr $(LIB) $(OBJS)
	$(Q)ranlib $(LIB)
	cp $(LIB) ../../../lib
	
$(OBJS): $(HDRS) $(SRCS)

clean:
	rm -Rf $(OBJS) $(LIB) $(SHAREDLIB)
