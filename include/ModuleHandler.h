#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include <dlfcn.h>
#include <string.h>
#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <pugixml.hpp>
#include <unordered_map>
#include <vector>

#include "Logger.h"
#include "ModuleInterface.h"
#include "SignalHandler.h"
#include "ParameterManager.h"

class ModuleHandler {
public:
    ModuleHandler(const char* modules_cfg, bool verbose);
    ~ModuleHandler() = default;
    int Init();
    int Run();
    int Deinit();

private:

    int Register_Modules();

    bool m_verbose;
    std::vector<std::shared_ptr<Module>> m_registered_modules;
    SharedData_t m_shared_data;
    SignalHandler m_sig_handler;
    RBLogger::Logger m_logger;

    std::unique_ptr<ParameterManager> m_parameter_manager;
};

#endif /* MODULEHANDLER_H */