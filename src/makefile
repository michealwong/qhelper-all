#注意这里面有业务名称，新业务开始建立时候请修改ROB_SER值
include ../include/make.macros

INCLUDE = $(SAS_INC) -I../include -I../comm -I../include/network

DEFINE_FlAG = -D$(ROB_SER)

#AutoRob和AutoRule后期建设重点
LIB = $(SAS_LIB) -L../lib -lossbasenetwork -lAutoRob 

DEBUG= -g

SCRS = $(wildcard *.c) $(wildcard *.cpp)

OBJS = $(SCRS:.c=.o) $(SCRS:.cpp=.o)

BINS = $(basename $(OBJS))

################################# target #####################################
all: update $(BINS)

update:
	svn up;
	cd ../cfg; svn up;cd -;
	cp ../cfg/* /usr/local/games/robgame/bin/$(ROB_SER)/cfg/
	cp ../tools/* /usr/local/games/robgame/bin/$(ROB_SER)/
	cd ../lib; svn up;cd -;
	cp ../lib/* /usr/local/games/robgame/bin/$(ROB_SER)/lib/ -vfR
	cd ../htdocs; svn up;cd -;
%:%.c
	g++ -w $<  -o $@ $(INCLUDE) $(LIB) $(COMMOBJ) $(DEBUG) $(DEFINE_FlAG)
	cp $@ /usr/local/games/robgame/bin/$(ROB_SER)/ -vf
%:%.cpp
	g++  -w $< -o  $@ $(INCLUDE) $(LIB) $(COMMOBJ) $(DEBUG) $(DEFINE_FlAG)
	cp $@ /usr/local/games/robgame/bin/$(ROB_SER)/ -vf
clean:
	rm -vfr $(BINS) 
