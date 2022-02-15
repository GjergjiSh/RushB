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
    int Parse_Configuration();
    int Register_Modules();
    int Assign_Module_Parameters(Module* module);

    const char* modules_cfg;
    pugi::xml_document modules_xml;
    std::vector<Module*> loaded_modules;
};

#endif /* SPIDER_H */