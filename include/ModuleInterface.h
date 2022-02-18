#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <unordered_map>

typedef struct {
    int top_servo;
    int right_servo;
    int left_servo;
} ServoValues_t;

typedef struct {
    float distance;
} UltraSonicValues_t;

typedef struct {
    ServoValues_t servos;
    UltraSonicValues_t uss;
} SharedData_t;

class Module {
public:
    Module(){};
    virtual ~Module(){};
    virtual int Init(void) = 0;
    virtual int Cycle_Step(void) = 0;
    virtual int Deinit(void) = 0;

    const char* name;
    std::unordered_map<std::string, std::string> parameters;
    void* lib_handle;
    SharedData_t* shared_data;
};

// Factory Methods
typedef Module* Create_t();
typedef void Destroy_t(Module*);

#endif /* MODULE_H */