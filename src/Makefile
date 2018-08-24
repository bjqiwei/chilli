APP =chilli
APPVERSION=1.0.6.1
INSTALL_PATH=/usr/local/$(APP)/

#CFLAGS='-D_EVENT_DISABLE_DEBUG_MODE -g -O1' ./configure --disable-shared
MOZJSDIR = ../libs/mozjs-45.0.2/js/src/

COMPILE = g++
COMPILECC = gcc

LINK = g++

SRC = ./
ACDSRC = ./ACD/
AgentSRC = ./Agent/
AvayaSRC = ./Avaya/
CallSRC = ./Call/
DeviceSRC = ./Device/
EventReportSrc = ./EventReport/
FreeSWITCHSrc = ./FreeSWITCH/
GroupSrc = ./Group/
IVRSrc = ./IVR/
modelSrc = ./model/
mysqlSrc = ./mysql/
ShSrc = ./Sh/
TCPSrc = ./TCP/
tinyxml2Src = ./tinyxml2/
websocketSrc =./websocket/

INCLUDE = -I./. -I../libs/fsm/ -I../libs/fsm/scxml -I../libs/apr-1.5.2/include -I../libs/apr-util-1.5.4/include -I../libs/FreeSWITCH/esl/include -I../libs/Avaya/TSAPI/hdrs

OBJ_DIR = ./obj/
ACD_OBJ_DIR = $(OBJ_DIR)ACD/
Agent_OBJ_DIR = $(OBJ_DIR)Agent/
Avaya_OBJ_DIR = $(OBJ_DIR)Avaya/
Call_OBJ_DIR = $(OBJ_DIR)Call/
Device_OBJ_DIR = $(OBJ_DIR)Device/
EventReport_OBJ_DIR = $(OBJ_DIR)EventReport/
FreeSWITCH_OBJ_DIR = $(OBJ_DIR)FreeSWITCH/
Group_OBJ_DIR = $(OBJ_DIR)Group/
IVR_OBJ_DIR = $(OBJ_DIR)IVR/
model_OBJ_DIR = $(OBJ_DIR)model/
mysql_OBJ_DIR = $(OBJ_DIR)mysql/
Sh_OBJ_DIR = $(OBJ_DIR)Sh/
TCP_OBJ_DIR = $(OBJ_DIR)TCP/
tinyxml2_OBJ_DIR = $(OBJ_DIR)tinyxml2/
websocket_OBJ_DIR = $(OBJ_DIR)websocket/


CFLAGS = -D__linux__ -D__LINUX__  -DSIGTSTP -DSIGQUIT -DAPPVERSION=$(APPVERSION) -c -g -O1 
CXXFLAGS = $(CFLAGS) -std=c++11

LDFLAGS= -L./. -L/usr/local/lib -L/usr/local/apr/lib/ -static-libstdc++ -static-libgcc -Wall -g -O1 
LDFLAGS:= $(LDFLAGS) ../libs/fsm/build/libfsm.a ../libs/FreeSWITCH/esl/libesl.a -lmysqlcppconn -lwebsockets -lapr-1 -laprutil-1 -ljsoncpp -lxml2 -levent_extra -levent_core -levent_pthreads -llog4cplus -lmozjs-45 -lmozglue\
	$(MOZJSDIR)mfbt/Compression.o $(MOZJSDIR)mfbt/Decimal.o $(MOZJSDIR)mfbt/Unified_cpp_mfbt0.o
LDFLAGS:= $(LDFLAGS) -lcrypto -lpthread -lm -ldl -lrt -lz -lm -ldl  -lrt -Wl,-rpath=./lib

OBJ = $(OBJ_DIR)chilli.o $(OBJ_DIR)uni_cmdline.o $(OBJ_DIR)uni_daemon.o\
	  $(ACD_OBJ_DIR)ACDModule.o $(ACD_OBJ_DIR)ACDDevice.o\
	  $(Agent_OBJ_DIR)AgentModule.o $(Agent_OBJ_DIR)Agent.o\
      $(Avaya_OBJ_DIR)AvayaACD.o $(Avaya_OBJ_DIR)AvayaAgent.o $(Avaya_OBJ_DIR)AvayaDevice.o $(Avaya_OBJ_DIR)AvayaAPI.o $(Avaya_OBJ_DIR)AvayaVDN.o $(Avaya_OBJ_DIR)TSAPIModule.o\
	  $(Call_OBJ_DIR)Call.o $(Call_OBJ_DIR)CallModule.o\
	  $(Device_OBJ_DIR)Device.o\
	  $(EventReport_OBJ_DIR)EventReportModule.o\
	  $(FreeSWITCH_OBJ_DIR)FreeSwitchDevice.o $(FreeSWITCH_OBJ_DIR)FreeSwitchModule.o\
	  $(Group_OBJ_DIR)Group.o $(Group_OBJ_DIR)GroupModule.o\
	  $(IVR_OBJ_DIR)IVRModule.o\
	  $(model_OBJ_DIR)PerformElement.o $(model_OBJ_DIR)ProcessModule.o\
	  $(mysql_OBJ_DIR)MySqlModule.o\
	  $(Sh_OBJ_DIR)ShAPI.o $(Sh_OBJ_DIR)ShDevModule.o $(Sh_OBJ_DIR)ShExtension.o\
	  $(TCP_OBJ_DIR)tcp.o\
	  $(tinyxml2_OBJ_DIR)tinyxml2.o\
	  $(websocket_OBJ_DIR)websocket.o
	  

APP:chkobjdir $(OBJ)
	$(LINK) -v -g -o $(APP)  $(OBJ) $(LDFLAGS)  

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

$(Call_OBJ_DIR)Call.o:$(CallSRC)Call.cpp
	$(COMPILE) $(CXXFLAGS) $(CallSRC)Call.cpp $(INCLUDE) -o $(Call_OBJ_DIR)Call.o

$(Call_OBJ_DIR)CallModule.o:$(CallSRC)CallModule.cpp
	$(COMPILE) $(CXXFLAGS) $(CallSRC)CallModule.cpp $(INCLUDE) -o $(Call_OBJ_DIR)CallModule.o
	
$(Device_OBJ_DIR)Device.o:$(DeviceSRC)Device.cpp
	$(COMPILE) $(CXXFLAGS) $(DeviceSRC)Device.cpp $(INCLUDE) -o $(Device_OBJ_DIR)Device.o
	
$(EventReport_OBJ_DIR)EventReportModule.o:$(EventReportSrc)EventReportModule.cpp
	$(COMPILE) $(CXXFLAGS) $(EventReportSrc)EventReportModule.cpp $(INCLUDE) -o $(EventReport_OBJ_DIR)EventReportModule.o
	
$(FreeSWITCH_OBJ_DIR)FreeSwitchDevice.o:$(FreeSWITCHSrc)FreeSwitchDevice.cpp
	$(COMPILE) $(CXXFLAGS) $(FreeSWITCHSrc)FreeSwitchDevice.cpp $(INCLUDE) -o $(FreeSWITCH_OBJ_DIR)FreeSwitchDevice.o
	
$(FreeSWITCH_OBJ_DIR)FreeSwitchModule.o:$(FreeSWITCHSrc)FreeSwitchModule.cpp
	$(COMPILE) $(CXXFLAGS) $(FreeSWITCHSrc)FreeSwitchModule.cpp $(INCLUDE) -o $(FreeSWITCH_OBJ_DIR)FreeSwitchModule.o
	
$(Group_OBJ_DIR)GroupModule.o:$(GroupSrc)GroupModule.cpp
	$(COMPILE) $(CXXFLAGS) $(GroupSrc)GroupModule.cpp $(INCLUDE) -o $(Group_OBJ_DIR)GroupModule.o
	
$(Group_OBJ_DIR)Group.o:$(GroupSrc)Group.cpp
	$(COMPILE) $(CXXFLAGS) $(GroupSrc)Group.cpp $(INCLUDE) -o $(Group_OBJ_DIR)Group.o
	
$(IVR_OBJ_DIR)IVRModule.o:$(IVRSrc)IVRModule.cpp
	$(COMPILE) $(CXXFLAGS) $(IVRSrc)IVRModule.cpp $(INCLUDE) -o $(IVR_OBJ_DIR)IVRModule.o

$(model_OBJ_DIR)PerformElement.o:$(modelSrc)PerformElement.cpp
	$(COMPILE) $(CXXFLAGS) $(modelSrc)PerformElement.cpp $(INCLUDE) -o $(model_OBJ_DIR)PerformElement.o
	
$(model_OBJ_DIR)ProcessModule.o:$(modelSrc)ProcessModule.cpp
	$(COMPILE) $(CXXFLAGS) $(modelSrc)ProcessModule.cpp $(INCLUDE) -o $(model_OBJ_DIR)ProcessModule.o
	
$(mysql_OBJ_DIR)MySqlModule.o:$(mysqlSrc)MySqlModule.cpp
	$(COMPILE) $(CXXFLAGS) $(mysqlSrc)MySqlModule.cpp $(INCLUDE) -o $(mysql_OBJ_DIR)MySqlModule.o
	
$(Sh_OBJ_DIR)ShAPI.o:$(ShSrc)ShAPI.cpp
	$(COMPILE) $(CXXFLAGS) $(ShSrc)ShAPI.cpp $(INCLUDE) -o $(Sh_OBJ_DIR)ShAPI.o
	
$(Sh_OBJ_DIR)ShDevModule.o:$(ShSrc)ShDevModule.cpp
	$(COMPILE) $(CXXFLAGS) $(ShSrc)ShDevModule.cpp $(INCLUDE) -o $(Sh_OBJ_DIR)ShDevModule.o
	
$(Sh_OBJ_DIR)ShExtension.o:$(ShSrc)ShExtension.cpp
	$(COMPILE) $(CXXFLAGS) $(ShSrc)ShExtension.cpp $(INCLUDE) -o $(Sh_OBJ_DIR)ShExtension.o
	
$(TCP_OBJ_DIR)tcp.o:$(TCPSrc)tcp.cpp
	$(COMPILE) $(CXXFLAGS) $(TCPSrc)tcp.cpp $(INCLUDE) -o $(TCP_OBJ_DIR)tcp.o
	
$(tinyxml2_OBJ_DIR)tinyxml2.o:$(tinyxml2Src)tinyxml2.cpp
	$(COMPILE) $(CXXFLAGS) $(tinyxml2Src)tinyxml2.cpp $(INCLUDE) -o $(tinyxml2_OBJ_DIR)tinyxml2.o
	
$(websocket_OBJ_DIR)websocket.o:$(websocketSrc)websocket.cpp
	$(COMPILE) $(CXXFLAGS) $(websocketSrc)websocket.cpp $(INCLUDE) -o $(websocket_OBJ_DIR)websocket.o
	
	
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
	
	@if test ! -d $(Call_OBJ_DIR);\
	then \
		mkdir $(Call_OBJ_DIR); \
	fi

	@if test ! -d $(Device_OBJ_DIR);\
	then \
		mkdir $(Device_OBJ_DIR); \
	fi	
	
	@if test ! -d $(EventReport_OBJ_DIR);\
	then \
		mkdir $(EventReport_OBJ_DIR); \
	fi
	
	@if test ! -d $(FreeSWITCH_OBJ_DIR);\
	then \
		mkdir $(FreeSWITCH_OBJ_DIR); \
	fi
	
	@if test ! -d $(Group_OBJ_DIR);\
	then \
		mkdir $(Group_OBJ_DIR); \
	fi
	
	@if test ! -d $(IVR_OBJ_DIR);\
	then \
		mkdir $(IVR_OBJ_DIR); \
	fi
	
	@if test ! -d $(model_OBJ_DIR);\
	then \
		mkdir $(model_OBJ_DIR); \
	fi

	@if test ! -d $(mysql_OBJ_DIR);\
	then \
		mkdir $(mysql_OBJ_DIR); \
	fi
	
	@if test ! -d $(Sh_OBJ_DIR);\
	then \
		mkdir $(Sh_OBJ_DIR); \
	fi

	@if test ! -d $(TCP_OBJ_DIR);\
	then \
		mkdir $(TCP_OBJ_DIR); \
	fi
	
	@if test ! -d $(tinyxml2_OBJ_DIR);\
	then \
		mkdir $(tinyxml2_OBJ_DIR); \
	fi
	
	@if test ! -d $(websocket_OBJ_DIR);\
	then \
		mkdir $(websocket_OBJ_DIR); \
	fi
	
clean:
	rm -rdf $(APP)
	rm -rf $(OBJ_DIR)*

install:
	mkdir $(INSTALL_PATH)
	cp ./$(APP) $(INSTALL_PATH)
	chmod g+x ./restart.sh
	cp ./restart.sh $(INSTALL_PATH)
	cp ./conf/* $(INSTALL_PATH)/conf
	#chmod g+x ./siad
	#cp -f ./siad /etc/init.d/

uninstall:
	rm -f $(INSTALL_PATH)$(APP)
	rm -rf $(INSTALL_PATH)conf
	rm -f $(INSTALL_PATH)restart.sh
	rm -rf $(INSTALL_PATH) 
	rm -rf /etc/init.d/siad

tar:
	@if [ "chilli" != "$(APP)" ]; \
	then \
		cp -f "./conf/chilli.xml" "./conf/$(APP).xml"; \
	fi
	
	sed -i '12s/^.*$//log4cplus.appender.D.File=.\/log\/$(APP)/' ./conf/log4cplus.properties;
	tar -zcvf ./$(APP).$(APPVERSION).tar.gz ./$(APP) ./conf/* ./lib/*
