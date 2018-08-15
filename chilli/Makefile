MODULE_APP =chilli
APPVERSION=1.0.5.0
INSTALL_PATH=/usr/local/chilli/

#CFLAGS='-D_EVENT_DISABLE_DEBUG_MODE -g -O1' ./configure --disable-shared
MOZJSDIR = ../libs/mozjs-45.0.2/js/src/

COMPILE = g++
COMPILECC = gcc

LINK = g++

SRC = ./
ACDSRC = ./ACD/
AgentSRC= ./Agent/
AvayaSRC= ./Avaya/

INCLUDE = -I./. -I../libs/fsm/ -I../libs/fsm/scxml -I../libs/apr-1.5.2/include -I../libs/apr-util-1.5.4/include -I../libs/freeswitch/esl/include -I../libs/Avaya/TSAPI/hdrs

OBJ_DIR = ./obj/
ACD_OBJ_DIR = $(OBJ_DIR)ACD/
Agent_OBJ_DIR = $(OBJ_DIR)Agent/
Avaya_OBJ_DIR = $(OBJ_DIR)Avaya/


CFLAGS = -D__linux__ -D__LINUX__ -DLUA_USE_LINUX -DSIGTSTP -DSIGQUIT -DAPPVERSION=$(APPVERSION) -DTRIMMED -c -g -O1 
CXXFLAGS = $(CFLAGS) -std=c++11

LDFLAGS= -L./. -L/usr/local/lib -static-libstdc++ -static-libgcc -Wall -g -O1 -lpthread 
LDFLAGS:= $(LDFLAGS) ../libs/jsoncpp-1.8.4/src/lib_json/libjsoncpp.a ../libs/fsm/build/libfsm.a ../libs/libxml2-2.9.3/.libs/libxml2.a $(MOZJSDIR)mozglue/build/libmozglue.a $(MOZJSDIR)js/src/libmozjs-45.so $(MOZJSDIR)mfbt/Compression.o $(MOZJSDIR)mfbt/Decimal.o $(MOZJSDIR)mfbt/Unified_cpp_mfbt0.o
LDFLAGS:= $(LDFLAGS) -lpthread -lm -ldl -lrt -lz -luuid -levent_extra -levent_core -levent_pthreads -llog4cplus  -llua -lm -ldl  -lrt

OBJ = $(OBJ_DIR)chilli.o $(OBJ_DIR)uni_cmdline.o $(OBJ_DIR)uni_daemon.o\
	  $(ACD_OBJ_DIR)ACDModule.o $(ACD_OBJ_DIR)ACDDevice.o\
	  $(Agent_OBJ_DIR)AgentModule.o $(Agent_OBJ_DIR)Agent.o\
      $(Avaya_OBJ_DIR)AvayaACD.o $(Avaya_OBJ_DIR)AvayaAgent.o $(Avaya_OBJ_DIR)AvayaDevice.o $(Avaya_OBJ_DIR)AvayaAPI.o $(Avaya_OBJ_DIR)AvayaVDN.o $(Avaya_OBJ_DIR)TSAPIModule.o\
	  $(OBJ_DIR)SiaHttpServer.o $(OBJ_DIR)SiaSession.o $(OBJ_DIR)SiaTcpMonitor.o\
	  $(OBJ_DIR)cfgFile.o $(OBJ_DIR)tinyxml2.o


MODULE_APP:chkobjdir $(OBJ)
	$(LINK) -v -g -o $(MODULE_APP)  $(OBJ) $(LDFLAGS)  

$(OBJ_DIR)chilli.o:$(SRC)chilli.cpp
	$(COMPILE) $(CXXFLAGS) $(SRC)chilli.cpp $(INCLUDE) -o $(OBJ_DIR)chilli.o

$(OBJ_DIR)uni_cmdline.o:$(SRC)uni_cmdline.cpp
	$(COMPILE) $(CXXFLAGS) -D_GLIBCXX_USE_SCHED_YIELD -D_GLIBCXX_USE_NANOSLEEP $(SRC)uni_cmdline.cpp $(INCLUDE) -o $(OBJ_DIR)uni_cmdline.o

$(OBJ_DIR)uni_daemon.o:$(SRC)uni_daemon.cpp
	$(COMPILE) $(CXXFLAGS) $(SRC)uni_daemon.cpp $(INCLUDE) -o $(OBJ_DIR)uni_daemon.o


$(ACD_OBJ_DIR)ACDModule.o:$(ACDSRC)ACDModule.cpp
	$(COMPILE) $(CXXFLAGS) $(ACDSRC)ACDModule.cpp $(INCLUDE) -o $(ACD_OBJ_DIR)ACDModule.o

$(ACD_OBJ_DIR)ACDDevice.o:$(ACDSRC)ACDDevice.cpp
	$(COMPILE) $(CXXFLAGS) $(ACDSRC)ACDDevice.cpp $(INCLUDE) -o $(ACD_OBJ_DIR)ACDDevice.o

$(Agent_OBJ_DIR)AgentModule.o:$(AgentSRC)AgentModule.cpp
	$(COMPILE) $(CXXFLAGS) $(AgentSRC)AgentModule.cpp $(INCLUDE) -o $(Agent_OBJ_DIR)AgentModule.o

$(Agent_OBJ_DIR)Agent.o:$(AgentSRC)Agent.cpp
	$(COMPILE) $(CXXFLAGS) $(AgentSRC)Agent.cpp $(INCLUDE) -o $(Agent_OBJ_DIR)Agent.o

$(Avaya_OBJ_DIR)AvayaACD.o:$(AvayaSRC)AvayaACD.cpp
	$(COMPILE) $(CXXFLAGS) $(AvayaSRC)AvayaACD.cpp $(INCLUDE) -o $(Avaya_OBJ_DIR)AvayaACD.o

$(Avaya_OBJ_DIR)AvayaAgent.o:$(AvayaSRC)AvayaAgent.cpp
	$(COMPILE) $(CXXFLAGS) $(AvayaSRC)AvayaAgent.cpp $(INCLUDE) -o $(Avaya_OBJ_DIR)AvayaAgent.o

$(Avaya_OBJ_DIR)AvayaAPI.o:$(AvayaSRC)AvayaAPI.cpp
	$(COMPILE) $(CXXFLAGS) $(AvayaSRC)AvayaAPI.cpp $(INCLUDE) -o $(Avaya_OBJ_DIR)AvayaAPI.o

$(Avaya_OBJ_DIR)AvayaDevice.o:$(AvayaSRC)AvayaDevice.cpp
	$(COMPILE) $(CXXFLAGS) $(AvayaSRC)AvayaDevice.cpp $(INCLUDE) -o $(Avaya_OBJ_DIR)AvayaDevice.o

$(Avaya_OBJ_DIR)AvayaVDN.o:$(AvayaSRC)AvayaVDN.cpp
	$(COMPILE) $(CXXFLAGS) $(AvayaSRC)AvayaVDN.cpp $(INCLUDE) -o $(Avaya_OBJ_DIR)AvayaVDN.o

$(Avaya_OBJ_DIR)TSAPIModule.o:$(AvayaSRC)TSAPIModule.cpp
	$(COMPILE) $(CXXFLAGS) $(AvayaSRC)TSAPIModule.cpp $(INCLUDE) -o $(Avaya_OBJ_DIR)TSAPIModule.o

$(Avaya_OBJ_DIR)SiaTcpMonitor.o:$(AvayaSRC)SiaTcpMonitor.cpp
	$(COMPILE) $(CXXFLAGS) $(AvayaSRC)SiaTcpMonitor.cpp $(INCLUDE) -o $(Avaya_OBJ_DIR)SiaTcpMonitor.o


$(OBJ_DIR)cfgFile.o:$(SIASRC)cfgFile.cpp
	$(COMPILE) $(CXXFLAGS) $(SIASRC)cfgFile.cpp $(INCLUDE) -o $(OBJ_DIR)cfgFile.o

$(OBJ_DIR)tinyxml2.o:$(SIASRC)tinyxml2.cpp
	$(COMPILE) $(CXXFLAGS) $(SIASRC)tinyxml2.cpp $(INCLUDE) -o $(OBJ_DIR)tinyxml2.o

chkobjdir:
	@if test ! -d $(OBJ_DIR);\
	then \
		mkdir $(OBJ_DIR); \
	fi
	
	@if test ! -d $(ACD_OBJ_DIR);\
	then \
		mkdir $(ACD_OBJ_DIR); \
	fi
	
	@if test ! -d $(Agent_OBJ_DIR);\
	then \
		mkdir $(Agent_OBJ_DIR); \
	fi
	
	@if test ! -d $(Avaya_OBJ_DIR);\
	then \
		mkdir $(Avaya_OBJ_DIR); \
	fi

clean:
	rm -rdf $(MODULE_APP)
	rm -rf $(OBJ_DIR)*

install:
	mkdir $(INSTALL_PATH)
	cp ./chilli $(INSTALL_PATH)
	chmod g+x ./restart.sh
	cp ./restart.sh $(INSTALL_PATH)
	cp ./conf/* $(INSTALL_PATH)/conf
	#chmod g+x ./siad
	#cp -f ./siad /etc/init.d/

uninstall:
	rm -f $(INSTALL_PATH)chilli
	rm -rf $(INSTALL_PATH)conf
	rm -f $(INSTALL_PATH)restart.sh
	rm -rf $(INSTALL_PATH) 
	rm -rf /etc/init.d/siad

tar:
	tar -zcvf ./chilli.$(APPVERSION).tar.gz ../Sia/ReadMe.txt ../Sia/restart.sh ../Sia/*.sh ../Sia/siaserver ../Sia/conf/log4cplus.properties ../Sia/conf/sia.cfg ../Sia/sys_scripts/dkjson.lua ../Sia/sys_scripts/init.lua ../Sia/sys_scripts/makecall.lua ../Sia/sys_scripts/preswitchboard.lua ../Sia/sys_scripts/satisfaction.lua
