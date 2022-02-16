CC = g++
CFLAGS = -ldl -Wall -g
BINS = Writer.so Reader.so

all: $(BINS)

Writer.so: Writer.cpp
	g++ -fPIC -shared -I/home/shorty/Repos/control-center/include -o Writer.so Writer.cpp

Reader.so: Reader.cpp
	g++ -fPIC -shared -I/home/shorty/Repos/control-center/include -o Reader.so Reader.cpp

clean:
	rm -rf $(BINS)
	rm -rf *.o
	rm -rf *.so