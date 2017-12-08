
MOZJSDIR = ../../libs/mozjs-45.0.2/js/src/


minitest:
	c++ -c  -DEXPORT_JS_API  -I$(MOZJSDIR)dist/include  -fPIC  -DMOZILLA_CLIENT -MD -MP -MF minitest.cpp.d -Wall -std=gnu++0x -pthread -pipe  minitest.cpp

	c++ -o minitest -Wall -static-libstdc++ -std=gnu++0x -pthread -pipe -DNDEBUG -g -O0  minitest.o -lpthread $(MOZJSDIR)mozglue/build/libmozglue.a $(MOZJSDIR)js/src/libjs_static.a $(MOZJSDIR)mfbt/Compression.o $(MOZJSDIR)mfbt/Decimal.o $(MOZJSDIR)mfbt/Unified_cpp_mfbt0.o -lm -ldl -lz -lm -ldl

clean:
	rm -rf minitest.o minitest.cpp.d minitest