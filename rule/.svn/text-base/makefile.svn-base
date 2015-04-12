
SAP_ROOT     = /usr/local/games
SAP_DEV		 = /data/SAPDEV

C++ = gcc
CC = gcc
LINK = gcc

INCLUDE = 
LIBS	= 
LIBS	+= 
LIBS	+=  

DEBUG = -g

CPPFILES =	$(wildcard *.cpp)
			
SHAREDLIB = libAutoRule.a

################################# target #####################################
all: update $(SHAREDLIB)
	@cp -vf $(SHAREDLIB) ../lib
	@cp -vf $(wildcard *.h) ../include
	
update: 
	svn up;

$(SHAREDLIB): $(CPPFILES:.cpp=.o)
	ar -rvl $@ $(CPPFILES:.cpp=.o) $(LIBS)
	

clean:
	rm -f $(SHAREDLIB) $(CPPFILES:.cpp=.o)

.SUFFIXES: .cpp .o

.cpp.o:	
	$(C++) -w -c -o $*.o $*.cpp $(INCLUDE) $(DEBUG)

