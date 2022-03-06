#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include <dlfcn.h>
#include <unistd.h>

#include <cstring>
#include <filesystem>
#include <iostream>
#include <pugixml.hpp>
#include <unordered_map>
#include <vector>

#include "IModuleInterface.h"
#include "Logger.h"
#include "ParameterManager.h"
#include "SignalHandler.h"

class ModuleManager {
public:
    ModuleManager(const char* modules_cfg, bool verbose);
    ~ModuleManager() = default;

    int Init();
    int Run();
    int Deinit();

private:
    int Register_Modules();
    int Init_Module(Module* const& module);

    Module* Create_Module(void* lib_handle);
    void Destroy_Module(void* lib_handle, Module* module);

    void* Get_Module_Handle(const std::filesystem::directory_entry& entry);
    Destroy_t* Get_Destroy_Symbol(void* lib_handle);
    Create_t* Get_Create_Symbol(void* lib_handle);

    bool m_verbose;
    std::vector<Module*> m_registered_modules;
    SharedData_t m_shared_data;
    SignalHandler m_sig_handler;
    RBLogger::Logger m_logger;

    std::unique_ptr<ParameterManager> m_parameter_manager;

    int Cycle_Module(Module* const& module);
};

#endif /* MODULEHANDLER_H */