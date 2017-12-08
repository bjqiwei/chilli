#请修改以下内容以确定相关内容

#项目类型(可执行程序exe,静态库lib,动态库dll,so)
export PROJECT_TYPE=a

#项目的版本号
export PROJECT_VERSION= 1.0.0.0

#源文件所在路径 （目录列表）
PROJECT_SOURCE= ./ ./scxml ./scxml/env ./scxml/model

#头文件路径(-I目录)
PROJECT_INCLUDE=-I./ -I./common -I../jsoncpp-src-0.5.0/include/ -I/usr/local/include/libxml2/ -I../mozjs-45.0.2/js/src/build/dist/include/ -I../mozjs-45.0.2/js/src/build/dist/system_wrappers -include ../mozjs-45.0.2/js/src/build/js/src/js-confdefs.h -include ../mozjs-45.0.2/config/gcc_hidden.h

#生成的版本文件名称
PROJCT_VERSION_H= 

#其他的链接路径，(-L目录)
PROJECT_LINK_DIR=-L../jsoncpp-src-0.5.0/libs/linux-gcc-6.1.0

#工程的宏定义
PROJECT_DEF= -D_LINUX -DLIBXML_STATIC -DEXPORT_JS_API -DMOZILLA_CLIENT 
# debug 工程的宏定义
export PROJECT_DEF_DEBUG= -D_DEBUG -DDEBUG
# release 工程的宏定义
export PROJECT_DEF_RELEASE= -DNDEBUG

#工程需要链接的其他动态库
export PROJECT_IMPORT_DLL= -lpthread -ldl

# debug 工程需要链接的其他静态库文件列表
export PROJECT_IMPORT_LIB_DEBUG=   

# release 工程需要链接的其他静态库文件列表
export PROJECT_IMPORT_LIB_RELEASE=    

#项目编译输出路径
export PROJECT_PATH = ./build
#项目输出文件主名称(不带后缀）
export PROJECT_BASENAME = libfsm



######################################################################
#--------------以下内容不需要修改------------------------------------#
######################################################################

export PROJECT_CC= g++
export PROJECT_LINKER= g++
export PROJECT_AR= ar rv
export PWD = $shell('pwd')

DLL_FLAG=
ifeq ($(PROJECT_TYPE),so)
DLL_FLAG= -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
endif

ifeq ($(PROJECT_TYPE),dll)
DLL_FLAG= -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
endif

#自动判断32位、64位系统
SYSBYTE := $(shell uname -r | grep 'x86_64')
ifeq ($(strip $(SYSBYTE)),) 
override SYSBYTE = -m32 
#-std=gnu++0x
else
override SYSBYTE = -m64 
#-std=gnu++0x
endif 

#编译用的编译器参数
export PROJECT_CPP_FLAGS = $(PROJECT_INCLUDE) $(DLL_FLAG) -fPIC -Wall -Wsign-compare -Wtype-limits -Wno-invalid-offsetof -Wcast-align -freorder-blocks -static-libstdc++ -static-libgcc $(SYSBYTE) $(PROJECT_DEF)

#链接用的参数
export PROJECT_EXE_LINK_FLAGS = $(PROJECT_LINK_DIR) -Wall $(SYSBYTE) -Wl,-rpath -Wl,.
export PROJECT_DLL_LINK_FLAGS = $(PROJECT_LINK_DIR) -Wall $(SYSBYTE) -shared -fPIC

#PROJECT源文件列表 
PROJECT_CPP_FILES :=$(foreach dir,$(PROJECT_SOURCE),$(wildcard $(dir)/*.cpp))
PROJECT_CXX_FILES :=$(foreach dir,$(PROJECT_SOURCE),$(wildcard $(dir)/*.cxx))
PROJECT_C_FILES :=$(foreach dir,$(PROJECT_SOURCE),$(wildcard $(dir)/*.c))

PROJECT_CPP_DEP := $(PROJECT_CPP_FILES:%.cpp=%.d)
PROJECT_CXX_DEP := $(PROJECT_CXX_FILES:%.cxx=%.d)
PROJECT_C_DEP := $(PROJECT_C_FILES:%.c=%.d)

export PROJECT_SRC_FILES :=$(PROJECT_CPP_FILES) $(PROJECT_CXX_FILES) $(PROJECT_C_FILES)
export PROJECT_DEPS := $(PROJECT_CPP_DEP) $(PROJECT_CXX_DEP) $(PROJECT_C_DEP)
export PROJECT_OBJS := $(PROJECT_DEPS:%.d=%.o)

default: debug

all: debug release

.PHONY :debug
debug: config
	@-mkdir -p debug
	@-mkdir -p $(PROJECT_PATH)
	@-make -f Makefile.debug


.PHONY: release
release: config
	@-mkdir -p release
	@-make -f Makefile.release
	@-mkdir -p $(PROJECT_PATH)


clean: clean-d clean-r

clean-d:
	#@-cd ../../log4cplus-1.1.3-rc2 && make clean
	@-make -f Makefile.debug clean
	@-rm -rf debug
	@-rm -rf  $(PROJECT_PATH)
	

clean-r:
	#@-cd ../../log4cplus-1.1.3-rc2 && make clean
	@-make -f Makefile.release clean
	@-rm -rf release
	@-rm -rf $(PROJECT_PATH)
	
config: ${PROJCT_VERSION_H}
	
${PROJCT_VERSION_H}: FORCE
	@echo "#ifndef __VERSION_H__" > $@.tmp
	@echo "#define __VERSION_H__" >> $@.tmp
	@echo "" >> $@.tmp
	@echo "#define APPLICATION_PROGRAM_VERSION      \"${PROJECT_VERSION}\"" >> $@.tmp
	@echo "#define APPLICATION_PROGRAM_BUILD_YEAR   \"`date +%Y`\"" >> $@.tmp
	@echo "#define APPLICATION_PROGRAM_BUILD_DATE   \"`date +%F`\"" >> $@.tmp
	@echo "#define APPLICATION_PROGRAM_BUILD_TIME   \"`date +%T`\"" >> $@.tmp
	@echo "#define APPLICATION_PROGRAM_BUILD_INFO   \"`$(PROJECT_CC) --version | head -n 1`\"" >> $@.tmp
	@echo "" >> $@.tmp
	@echo "#endif" >> $@.tmp
	@echo "" >> $@.tmp
	@if cmp -s $@.tmp $@ ; then :; else \
		mv $@.tmp $@ ; \
	fi
	@rm -f $@.tmp

FORCE:

