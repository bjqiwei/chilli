make 步骤
1、解压autoconf-2.65.tar.gz,进入目录 ./configure && make && make install
2、解压automake-1.15.tar.gz,进入目录 ./configure && make && make install
3、解压automake-1.14.tar.gz,进入目录 ./configure && make && make install
4、进入 log4cplus-1.2.0 ./configure CXXFLAGS="-std=c++11"  --without-qt --without-qt5 --without-python --enable-static && make && make install
5、libevent,使用yum 安装libevent最新版本
6、libxml2,使用 yum 安装libxml2 最新版本
7、libmozjs,使用yum安装，yum install mozjs38
8、进入jsoncpp-1.8.4目录,cmake -DCMAKE_BUILD_TYPE=release -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=ON -DARCHIVE_INSTALL_DIR=. -G "Unix Makefiles" && make && make install
9、 进入mysql代码目录 cmake -DBUILD_STATIC=ON  . -G "Unix Makefiles" && make && make install
10、openssl, 使用yum install openssl 安装
11、libapr, yum install apr-devel apr-util-devel
12、进入lib/FreeSWITCH 代码目录, make 
13、进入fsm 目录 make
14、进入 src 目录，make