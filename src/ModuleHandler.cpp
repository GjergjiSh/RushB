#include "ModuleHandler.h"
#include  <chrono>

ModuleHandler::ModuleHandler(const char* modules_cfg, bool verbose) : modules_cfg(modules_cfg), verbose(verbose)
{
    LOG_INFO(std::string("ModuleHandler Version: ").append(VERSION));
    memset(&shared_data, 0, sizeof(shared_data));
}

ModuleHandler::~ModuleHandler(){}

int ModuleHandler::Init()
{
    // Parse the XML Configuration File
    if (Parse_Configuration() != 0)
        return -1;

    // Load the Modules in the lib folder
    if (Register_Modules() != 0)
        return -1;

    // Initialize each loaded module
    for (auto module : registered_modules) {
        if (module->Init() != 0) {
            LOG_ERROR(std::string("Failed to initialize module: ").append(module->name));
            return -1;
        };
    }
    LOG_INFO("Initialization finished");
    return 0;
}

int ModuleHandler::Deinit()
{
    for (auto module : registered_modules) {
        module->Deinit();

        Destroy_t* Destroy_Module = (Destroy_t*)dlsym(module->lib_handle, "Destroy");
        const char* dlsym_error = dlerror();
        if (dlsym_error)
            LOG_ERROR_DESCRIPTION("Failed to load symbol destroy: ", dlsym_error)

        Destroy_Module(module);

        if (dlclose(module->lib_handle) != 0)
            LOG_ERROR_DESCRIPTION("Failed to destroy module :", dlerror());
    }
    LOG_INFO("Deinitialization finished");
    return 0;
}

int ModuleHandler::Run()
{
    // Trigger cycle for each registered module
    for (auto module : registered_modules) {
        if (verbose) {
            // Print cycle time for each module
            auto start = std::chrono::system_clock::now();
            if (module->Cycle_Step() != 0) {
                LOG_ERROR_DESCRIPTION("Cycle Step failed for module: ", module->name);
                return -1;
            };
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            LOG_TIME_INFO(std::string("Cycle target: ").append(module->name), elapsed.count());
        } else {
            if (module->Cycle_Step() != 0) {
                LOG_ERROR_DESCRIPTION("Cycle Step failed for module: ", module->name);
                return -1;
            };
        }
    }
    return 0;
}

int ModuleHandler::Parse_Configuration()
{
    // Load XML config file into memory
    pugi::xml_parse_result parse_result = modules_xml.load_file(modules_cfg);
    if (!parse_result) {
        LOG_ERROR_DESCRIPTION("Failed to parse the modules configuration file",
            parse_result.description());
        return -1;
    }
    return 0;
}

int ModuleHandler::Register_Modules()
{
    auto start = std::chrono::system_clock::now();
    // Iterate the available libraries in the lib folder
    for (const auto & entry : std::filesystem::directory_iterator("./modules")) {
        // Load the library
        void* lib_handle = dlopen(entry.path().c_str(), RTLD_LAZY);
        if (!lib_handle) {
            LOG_ERROR_DESCRIPTION("Failed to load library: ", dlerror());
            return -1;
        }

        // reset errors
        dlerror();

        // load the Create Symbol of the Module
        Create_t* Create_Module = (Create_t*)dlsym(lib_handle, "Create");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            LOG_ERROR_DESCRIPTION("Failed to load symbol create: ", dlsym_error);
            return -1;
        }

        // Create the Module Instance
        Module* module = Create_Module();
        module->lib_handle = lib_handle;
        module->shared_data = &shared_data;

        // Only register if the module is in the XML config
        pugi::xml_node module_node = modules_xml.child("modules").find_child_by_attribute("name", module->name);
        if (!module_node) {
            delete module;
            continue;
        }

        // Assign the parameters defined in the XML config to the Module
        Assign_Module_Parameters(module);

        // Register the Module Instance
        registered_modules.push_back(module);
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    LOG_TIME_INFO("Finished registering modules", elapsed.count());
    return 0;
}

int ModuleHandler::Assign_Module_Parameters(Module* module)
{
    // Find the module's node in the XML config file
    pugi::xml_node module_node = modules_xml.child("modules").find_child_by_attribute("name", module->name);
    pugi::xml_node parameters_node = module_node.child("parameters");

    // Assign the parameter names and values to the module
    for (pugi::xml_node parameter : parameters_node.children()) {
                auto name = parameter.attribute("name").value();
                auto val = parameter.attribute("value").value();
                module->parameters.insert(std::make_pair(name,val));
    }

    // Print the assigned configuration
    Print_Module_Parameters(module);
    return 0;
}

void ModuleHandler::Print_Module_Parameters(Module* module)
{
    for (auto parameter : module->parameters) {
        std::cout << "[I][" << module->name << "]"
                  << " Parameter: " << parameter.first
                  << " Value: " << parameter.second
                  << std::endl;
    }
}

