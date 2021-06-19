#-------------------------------------------------
libraries=$(HOME)/Development/trueblocks-core/src/libs
cflags=-std=c++11 -Werror -Wall -O2 -I. -I$(libraries)/utillib -I$(libraries)/etherlib -I$(libraries)/acctlib
curl_on_mac=/Library/Developer/CommandLineTools/SDKs/MacOSX11.1.sdk/usr/lib/libcurl.4.tbd

none:
	@echo "Run either 'make mac' or 'make linux'."

mac:
	g++ $(cflags) -fPIC -shared -o libcompound.dylib $(libraries)/*.a $(curl_on_mac) compound.cpp
	mv ./libcompound.dylib ~/Library/Application\ Support/TrueBlocks/cache/objs/

linux:
	@echo g++ $(cflags) -fPIC -shared -o libcompound.so $(libraries)/*.a compound.cpp
	@echo mv ./libcompound.so ~/.local/share/trueblocks/cache/objs/
