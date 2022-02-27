#ifndef MODULE_H
#define MODULE_H

#include "Logger.h"

#include <iostream>
#include <unordered_map>

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
    Module(){};
    virtual ~Module(){};
    virtual int Init(void) = 0;
    virtual int Cycle_Step(void) = 0;
    virtual int Deinit(void) = 0;

    std::string name;
    std::unordered_map<std::string, std::string> parameters;
    void* lib_handle;
    SharedData_t* shared_data;

    Logger logger;

};

// Factory Methods
typedef Module* Create_t();
typedef void Destroy_t(Module*);

#endif /* MODULE_H */