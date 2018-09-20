make 步骤
1、 yum install libevent-devel libxml2-devel mozjs38-devel openssl-devel apr-devel apr-util-devel libwebsockets-devel libuuid-devel mysql-devel jsoncpp-devel
2、解压autoconf-2.65.tar.gz,进入目录 ./configure && make && make install
3、解压automake-1.15.tar.gz,进入目录 ./configure && make && make install
4、解压automake-1.14.tar.gz,进入目录 ./configure && make && make install
5、进入 log4cplus-1.2.0 ./configure CXXFLAGS="-std=c++11"  --without-qt --without-qt5 --without-python --enable-static && make && make install 
6、进入libs/FreeSWITCH/esl 代码目录, make 
7、进入fsm 目录 make
8、进入 src 目录，make