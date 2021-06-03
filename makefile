#-------------------------------------------------
#home=/Users/jrush
home=/home/jrush

libraries=$(home)/Development/trueblocks-core/src/libs
cflags=-std=c++11 -Werror -Wall -O2 -I. -I$(libraries)/utillib -I$(libraries)/etherlib -I$(libraries)/acctlib
curl=/Library/Developer/CommandLineTools/SDKs/MacOSX11.1.sdk/usr/lib/libcurl.4.tbd

none:
	@echo "Run either 'make mac' or 'make linux'."

mac:
	g++ $(cflags) -fPIC -shared -o libmatt.dylib $(libraries)/*.a $(curl) matt.cpp
	mv ./libmatt.dylib ~/Library/Application\ Support/TrueBlocks/cache/objs/

linux:
	g++ $(cflags) -fPIC -shared -o libmatt.so $(libraries)/*.a matt.cpp
	mv ./libmatt.so ~/.local/share/trueblocks/cache/objs/
