LIB_INSTALL_DIR=~/lib
INCLUDE_INSTALL_DIR=~/include

all: build test


install: build
	cp build/libpsk.so build/libpsk.a $(LIB_INSTALL_DIR)
	cp src/psk.h++ $(INCLUDE_INSTALL_DIR)


build: build/libpsk.so build/libpsk.a

build/libpsk.a: psk.h++ psk.c++
	g++ -Wall -c -fpic -o build/libpsk.a psk.c++

build/libpsk.so: build/libpsk.a
	g++ -Wall -shared -fpic -o build/libpsk.so build/libpsk.a




test: test/psk-test 

test/psk-test: psk-test.c++ build/libpsk.a
	g++ -Wall -o test/psk-test psk-test.c++ -Wl,-Bstatic -Lbuild -lpsk -Wl,-Bdynamic `Magick++-config --cppflags --cxxflags --ldflags --libs`
