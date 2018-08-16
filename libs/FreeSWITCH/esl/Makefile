MODULE_APP =libesl.a

#CFLAGS='-D_EVENT_DISABLE_DEBUG_MODE -g -O1' ./configure --disable-shared

INSTALL_PATH=/usr/local/lib
COMPILE = g++
COMPILECC = gcc

LINK = ar rv

SRC = ./

INCLUDE = -I./include

OUTPUTOBJ = ./obj/

#自动判断32位、64位系统
SYSBYTE := $(shell uname -r | grep 'x86_64')
ifeq ($(strip $(SYSBYTE)),) 
override SYSBYTE = -m32 
#-std=gnu++0x
else
override SYSBYTE = -m64 
#-std=gnu++0x
endif 

CFLAGS = -D__LINUX__  -c -g -O1 $(SYSBYTE)
CXXFLAGS = $(CFLAGS) -std=c++11

LDFLAGS=

OBJ = $(OUTPUTOBJ)esl.o $(OUTPUTOBJ)esl_buffer.o $(OUTPUTOBJ)esl_config.o $(OUTPUTOBJ)esl_event.o \
      $(OUTPUTOBJ)esl_json.o $(OUTPUTOBJ)esl_oop.o $(OUTPUTOBJ)esl_threadmutex.o


MODULE_APP:chkobjdir $(OBJ)
	$(LINK) $(MODULE_APP)  $(OBJ) $(LDFLAGS)  

$(OUTPUTOBJ)esl.o:$(SRC)esl.c
	$(COMPILECC) $(CFLAGS) $(SRC)esl.c $(INCLUDE) -o $(OUTPUTOBJ)esl.o

$(OUTPUTOBJ)esl_buffer.o:$(SRC)esl_buffer.c
	$(COMPILECC) $(CFLAGS) $(SRC)esl_buffer.c $(INCLUDE) -o $(OUTPUTOBJ)esl_buffer.o

$(OUTPUTOBJ)esl_config.o:$(SRC)esl_config.c
	$(COMPILECC) $(CFLAGS) $(SRC)esl_config.c $(INCLUDE) -o $(OUTPUTOBJ)esl_config.o

$(OUTPUTOBJ)esl_event.o:$(SRC)esl_event.c
	$(COMPILECC) $(CFLAGS) $(SRC)esl_event.c $(INCLUDE) -o $(OUTPUTOBJ)esl_event.o

$(OUTPUTOBJ)esl_json.o:$(SRC)esl_json.c
	$(COMPILECC) $(CFLAGS) $(SRC)esl_json.c $(INCLUDE) -o $(OUTPUTOBJ)esl_json.o

$(OUTPUTOBJ)esl_oop.o:$(SRC)esl_oop.cpp
	$(COMPILE) $(CXXFLAGS) $(SRC)esl_oop.cpp $(INCLUDE) -o $(OUTPUTOBJ)esl_oop.o

$(OUTPUTOBJ)esl_threadmutex.o:$(SRC)esl_threadmutex.c
	$(COMPILECC) $(CFLAGS) $(SRC)esl_threadmutex.c $(INCLUDE) -o $(OUTPUTOBJ)esl_threadmutex.o

clean:
	rm -rdf $(MODULE_APP)
	rm -rf $(OUTPUTOBJ)*
	
chkobjdir:
	@if test ! -d $(OUTPUTOBJ);\
	then \
		mkdir $(OUTPUTOBJ); \
	fi
