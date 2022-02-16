PRJ_PATH = -I./include

BUILD_PATH = ./bin

LIB_PATH = $(BUILD_PATH)/modules

OBJ_PATH = $(BUILD_PATH)/obj

POST_BUILD = @mv

COPY = @cp

OBJ_PRJ = $(OBJ_PATH)/ModuleHandler.o $(OBJ_PATH)/Main.o

CC = g++ -std=c++17 -static-libgcc -static-libstdc++ -fPIC $(PRJ_PATH) -m64 -msse2 -Wall -O2 -O3 -Wno-comment -Wno-deprecated-declarations -pthread -c

LD = g++ -static-libgcc -static-libstdc++ -m64 -Wall -Wl,--copy-dt-needed-entries

LIB_PRJ = -lpugixml -ldl

all: $(OBJ_PATH) $(BUILD_PATH) $(LIB_PATH) ControlCenter $(POST_BUILD)

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(LIB_PATH):
	mkdir -p $(LIB_PATH)

$(POST_BUILD):
	$(POST_BUILD) ControlCenter $(BUILD_PATH)
	@cp ./resources/Modules.xml $(BUILD_PATH)

ControlCenter: $(OBJ_PRJ)
	$(LD) $(OBJ_PRJ) $(LIB_PRJ) -o ControlCenter

$(OBJ_PATH)/Main.o: ./src/Main.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/ModuleHandler.o: ./src/ModuleHandler.cpp
	$(CC) -o $@ $?

clean:
	rm -f -v -R $(OBJ_PATH)
	rm -f -v -R $(BUILD_PATH)