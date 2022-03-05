#ifndef MODULE_H
#define MODULE_H

#include <memory>
#include <iostream>
#include <unordered_map>

#include "Logger.h"

#define IMAGE_1920X1080_R8G8B8 (1920 * 1080 * 3)

#pragma pack(push, 1)
typedef struct {
    int top_servo;
    int right_servo;
    int left_servo;
} ServoValues_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    float distance;
} UltraSonicValues_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef unsigned char ImageFrame_t[IMAGE_1920X1080_R8G8B8];
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    ImageFrame_t frame;
} VideoData_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    ServoValues_t servos;
    UltraSonicValues_t uss;
    VideoData_t video;
} SharedData_t;
#pragma pack(pop)

class Module {
public:
    Module() {};

    virtual ~Module() {};

    virtual int Init() = 0;

    virtual int Cycle_Step() = 0;

    virtual int Deinit() = 0;

    std::string name;
    std::unordered_map<std::string, std::string> parameters;
    SharedData_t *shared_data;
    void *lib_handle;

    RBLogger::Logger logger;

};

// Factory Methods
typedef std::shared_ptr<Module> Create_t();

extern "C" {
    std::shared_ptr<Module>Create_Instance();
}

#endif /* MODULE_H */