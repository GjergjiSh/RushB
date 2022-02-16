#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include "LogUtils.h"
#include "Module.h"
#include <dlfcn.h>
#include <filesystem>
#include <iostream>
#include <memory>
#include <pugixml.hpp>
#include <unordered_map>
#include <vector>

class ModuleHandler {
public:
    ModuleHandler(const char* modules_cfg);
    ~ModuleHandler();
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

#endif /* MODULEHANDLER_H */