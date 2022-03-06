#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include <dlfcn.h>
#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <pugixml.hpp>
#include <unordered_map>
#include <vector>
#include <cstring>

#include "Logger.h"
#include "IModuleInterface.h"
#include "SignalHandler.h"
#include "ParameterManager.h"

class ModuleManager {
public:
    ModuleManager(const char *modules_cfg, bool verbose);
    ~ModuleManager() = default;

    int Init();
    int Run();
    int Deinit();

private:

    int Register_Modules();
    Create_t *Load_Module_Create_Symbol(void *lib_handle);
    Destroy_t *Load_Module_Destroy_Symbol(void *lib_handle);

    bool m_verbose;
    std::vector<Module *> m_registered_modules;
    SharedData_t m_shared_data;
    SignalHandler m_sig_handler;
    RBLogger::Logger m_logger;

    std::unique_ptr<ParameterManager> m_parameter_manager;
};

#endif /* MODULEHANDLER_H */