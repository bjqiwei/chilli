本项目主要想建立一个通用型的CTI,适合小规模用户使用，包括IVR、软电话、ACD、数据库、录音等功能。

make 步骤
1、解压autoconf-2.65.tar.gz,进入目录 ./configure && make && make install
2、解压automake-1.15.tar.gz,进入目录 ./configure && make && make install
3、解压automake-1.14.tar.gz,进入目录 ./configure && make && make install
4、进入 log4cplus-1.2.0 ./configure --without-qt --without-qt5 --without-python --enable-static && make && make install
5、解压libevent-2.1.8-stable.tar.gz，进入目录 ./configure --enable-static && make && make install
6、解压libxml2-2.9.3.tar.gz，进入目录，./configure --enable-static && make && make install
7、解压mozjs-45.0.2.tar.bz2，进入js/src目录，./configure --disable-tests --disable-readline --disable-build-backend --disable-xterm-updates --disable-jemalloc --without-system-zlib --without-intl-api --without-nspr --disable-optimize --enable-static-rtl --disable-shared-js --disable-shared --enable-static && make && make install
8、进入jsoncpp-src-0.5.0目录  scons platform=linux-gcc
9、进入fms 目录 make
10、进入 chilli 主程序目录，make