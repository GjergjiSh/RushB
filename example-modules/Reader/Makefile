PRJ_PATH = -I./include -I../../include

BUILD_PATH = ./build

OBJ_PATH = ${BUILD_PATH}/obj

POST_BUILD = @mv

OBJ_PRJ = $(OBJ_PATH)/Reader.o \

CC = g++ -std=c++17 -static-libgcc -static-libstdc++ -fPIC $(PRJ_PATH) -m64 -msse2 -Wall -O2 -Wno-comment -c

LD = g++ -static-libgcc -static-libstdc++ -m64 -Wall -shared -Wl,-rpath=./,-soname,Reader.so -o Reader.so

LIB_PRJ = 

all:  $(OBJ_PATH) $(BUILD_PATH) Reader.so $(POST_BUILD)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

Reader.so: $(OBJ_PRJ)
	$(LD) $(OBJ_PRJ) $(LIB_PRJ)

$(OBJ_PATH)/Reader.o: ./src/Reader.cpp
	$(CC) -o $@ $?

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(POST_BUILD):

clean:
	rm -f -v *.so
	rm -f -v -R $(BUILD_PATH)