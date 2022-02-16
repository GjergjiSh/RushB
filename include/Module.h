#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <unordered_map>

class Module {
public:
    Module(){}; //: name({}), parameters({}){};
    virtual ~Module(){};
    virtual int Init(void) = 0;
    virtual int Cycle_Step(void) = 0;
    virtual int Deinit(void) = 0;

    const char* name;
    std::unordered_map<std::string, std::string> parameters;
    void* lib_handle;

    //Shared Methods
    void Print_Config() {
        for (auto parameter : parameters) {
            std::cout << "[I][" << name << "]"
                      << " Parameter: " << parameter.first
                      << " Value: " << parameter.second
                      << std::endl;
        }
    }
};

typedef Module* Create_t();
typedef void Destroy_t(Module*);

#endif /* MODULE_H */