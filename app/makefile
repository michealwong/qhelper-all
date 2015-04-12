
SAP_ROOT     = /usr/local/games
SAP_DEV		 = /data/SAPDEV

C++ = gcc
CC = gcc
LINK = gcc

INCLUDE = -I../include -I$(SAP_DEV)/util
INCLUDE += -I/data/SAPDEV/include/mysql

LIBS	= 
LIBS	+=  $(SAP_DEV)/util/comm_strings.o
LIBS	+=  $(SAP_DEV)/lib/libmysqlclient.so
LIBS	+=  $(SAP_DEV)/lib/libmysqlclient.so.16
LIBS	+=  $(SAP_DEV)/util/DataOper.o

DEBUG = -g

CPPFILES =	$(wildcard *.cpp)
			
SHAREDLIB = libGameApi.a

################################# target #####################################
all: update $(SHAREDLIB)
	@cp -vf $(SHAREDLIB) ../lib
	@cp -vf $(wildcard *.h) ../include
	
update: 
	svn up;

$(SHAREDLIB): $(CPPFILES:.cpp=.o)
	ar -rvl $@ $(CPPFILES:.cpp=.o)
	

clean:
	rm -f $(SHAREDLIB) $(CPPFILES:.cpp=.o)

.SUFFIXES: .cpp .o

.cpp.o:	
	$(C++) -w -c -o $*.o $*.cpp $(INCLUDE) $(DEBUG)

