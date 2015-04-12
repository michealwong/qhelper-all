#注意这里面有业务名称，新业务开始建立时候请修改ROB_SER值
include ../include/make.macros
C++ = gcc

LINK = gcc
INCLUDE = -I./
INCLUDE += -I../include
INCLUDE += -I../include/libxml2/
INCLUDE += -I../include/wsclient/logmanager
INCLUDE += -I../include/wsclient/dbmanager
INCLUDE += -I../include/curl
INCLUDE += -I../include/result_xml
INCLUDE += -I../include/xercesc
INCLUDE += -I../include/network
INCLUDE += -I../include/tlog/

INCLUDE_FLAG = -include $(INCLUDE) -include sap.nsmap 

DEFINE_FlAG = -D$(ROB_SER)

CORE_LINK_LIBS = -lpthread -ldl -lstdc++ -L./ -L./result_xml/Altova -L./result_xml/AltovaXML -L./result_xml/sap
MODULE_LIBS = -lxml2 -lAltovaXML -lAltova -lsap -lsap_func -lossbasenetwork -lxerces-c -L../lib -ltsf4g -Wl,-rpath,./
SHARED = -shared -fPCI
LIBS = $(CORE_LINK_LIBS) $(MODULE_LIBS) $(SHARED)
LINKOPTS = -L../lib


DEBUG = -g

CPPFILES =	$(wildcard *.cpp)

SHAREDLIB = libAutoRob.so
STATICLIB = libAutoRob.a




################################# target #####################################
all: update $(SHAREDLIB)
	@cp -vf $(SHAREDLIB) ../lib
	@cp -vf $(wildcard *.h) ../include
	
update: 
	svn up;

$(STATICLIB): $(CPPFILES:.cpp=.o)
	ar -rvl $@ $(CPPFILES:.cpp=.o) $(LIBS) $(DEFINE_FlAG)

$(SHAREDLIB): $(CPPFILES:.cpp=.o)
	$(LINK) -o $@ $(CPPFILES:.cpp=.o) $(LINKOPTS) $(LIBS) $(DEFINE_FlAG)
clean:
	rm -f $(SHAREDLIB) $(CPPFILES:.cpp=.o)
	rm -f $(STATICLIB) $(CPPFILES:.cpp=.o)

.SUFFIXES: .cpp .o

.cpp.o:	
	$(C++) -w -c -o $*.o $*.cpp $(INCLUDE) $(DEBUG) -fPIC  $(DEFINE_FlAG)

