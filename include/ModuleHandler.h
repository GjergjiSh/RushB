#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include "Logger.h"
#include "ModuleInterface.h"
#include "SignalHandler.h"

#include <dlfcn.h>
#include <filesystem>
#include <iostream>
#include <memory>
#include <pugixml.hpp>
#include <unordered_map>
#include <vector>
#include <string.h>

class ModuleHandler {
public:
    ModuleHandler(const char* modules_cfg, bool verbose);
    ~ModuleHandler() = default;
    int Init();
    int Run();
    int Deinit();

private:
    int Parse_Configuration();
    int Register_Modules();
    int Assign_Module_Parameters(std::shared_ptr<Module> module);
    void Print_Module_Parameters(std::shared_ptr<Module> module);

    const char* modules_cfg;
    bool verbose;
    pugi::xml_document modules_xml;
    std::vector<std::shared_ptr<Module>> registered_modules;
    SharedData_t shared_data;
    SignalHandler sig_handler;
    RBLogger::Logger logger;
};

#endif /* MODULEHANDLER_H */