#ifndef SPIDER_H
#define SPIDER_H

#include "LogUtils.h"
#include "Module.h"
#include <dlfcn.h>
#include <filesystem>
#include <iostream>
#include <memory>
#include <pugixml.hpp>
#include <unordered_map>
#include <vector>

class Spider {
public:
    Spider(const char* modules_cfg);
    ~Spider();
    int Init();
    int Run();
    int Deinit();

private:
    int Parse_Configuration();
    int Register_Modules();
    int Assign_Module_Parameters(Module* module);

    const char* modules_cfg;
    pugi::xml_document modules_xml;
    std::vector<Module*> loaded_modules;
    const char* VERSION = "0.1";
};

#endif /* SPIDER_H */