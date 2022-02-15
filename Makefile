PRJ_PATH = -I./include

BUILD_PATH = ./bin

LIB_PATH = $(BUILD_PATH)/lib

OBJ_PATH = $(BUILD_PATH)/obj

POST_BUILD = @mv

OBJ_PRJ = $(OBJ_PATH)/Spider.o $(OBJ_PATH)/Main.o

CC = g++ -std=c++17 -static-libgcc -static-libstdc++ -fPIC $(PRJ_PATH) -m64 -msse2 -Wall -O2 -O3 -Wno-comment -Wno-deprecated-declarations -pthread -c

LD = g++ -static-libgcc -static-libstdc++ -m64 -Wall -Wl,--copy-dt-needed-entries

LIB_PRJ = -lpugixml -ldl

all: $(OBJ_PATH) $(BUILD_PATH) $(LIB_PATH) Spider $(POST_BUILD)

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(LIB_PATH):
	mkdir -p $(LIB_PATH)

$(POST_BUILD):
	$(POST_BUILD) Spider $(BUILD_PATH)

Spider: $(OBJ_PRJ)
	$(LD) $(OBJ_PRJ) $(LIB_PRJ) -o Spider

$(OBJ_PATH)/Main.o: ./src/Main.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/Spider.o: ./src/Spider.cpp
	$(CC) -o $@ $?

clean:
	rm -f -v -R $(OBJ_PATH)
	rm -f -v -R $(BUILD_PATH)