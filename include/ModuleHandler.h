#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include <dlfcn.h>
#include <string.h>

#include <filesystem>
#include <iostream>
#include <pugixml.hpp>
#include <unordered_map>
#include <vector>

#include "Logger.h"
#include "ModuleInterface.h"
#include "SignalHandler.h"

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

    const char* m_modules_cfg;
    bool m_verbose;
    pugi::xml_document m_modules_xml;
    std::vector<std::shared_ptr<Module>> m_registered_modules;
    SharedData_t m_shared_data;
    SignalHandler m_sig_handler;
    RBLogger::Logger m_logger;
};

#endif /* MODULEHANDLER_H */