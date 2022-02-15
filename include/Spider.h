#ifndef SPIDER_H
#define SPIDER_H

#include <pugixml.hpp>
#include <vector>
#include <iostream>
#include "Common.h"
#include <unordered_map>
#include "Module.h"
#include <memory>
#include <dlfcn.h>
#include <filesystem>

class Spider {
public:
    Spider(const char* modules_cfg);
    ~Spider();
    int Init();
    int Run();
    int Deinit();

private:
    int Register_Modules();
    int Load_Modules();
    int Configure_Modules();

    const char* modules_cfg;
    std::unordered_map<Module*, void*> loaded_modules;
};

#endif /* SPIDER_H */