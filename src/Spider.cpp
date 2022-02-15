#include "Spider.h"


Spider::Spider(const char* modules_cfg) : modules_cfg(modules_cfg)
{

}

Spider::~Spider()
{

}

int Spider::Init()
{
    // Parse the XML Configuration File
    if (Parse_Configuration() != 0) {
        return -1;
    }

    // Load the Modules in the lib folder
    if (Register_Modules() != 0) {
        return -1;
    }

    // Initialize each loaded module
    for (auto module : loaded_modules) {
        if (module->Init() != 0) {
            LOG_ERROR("Failed to initialize module"); //missing name for log
            return -1;
        };
    }

    LOG_INFO("Initialization finished");
    return 0;
}

int Spider::Deinit()
{
    for (auto module : loaded_modules) {

        module->Deinit();

        Destroy_t* Destroy_Module = (Destroy_t*)dlsym(module->lib_handle, "Destroy");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            LOG_ERROR_DESCRIPTION("Failed to load symbol destroy: ", dlsym_error)
        }

        Destroy_Module(module);

        if (dlclose(module->lib_handle) != 0) {
            LOG_ERROR_DESCRIPTION("Failed to destroy module :", dlerror());
        };
    }
    LOG_INFO("Deinitialization finished");
    return 0;
}

int Spider::Run()
{
    for (auto module : loaded_modules) {
        module->Cycle_Step();
    }
    return 0;
}

int Spider::Parse_Configuration()
{
    pugi::xml_parse_result parse_result = modules_xml.load_file(modules_cfg);
    if (!parse_result) {
        LOG_ERROR_DESCRIPTION("Failed to parse the modules configuration file",
            parse_result.description());
        return -1;
    }
    return 0;
}

int Spider::Register_Modules()
{
    // Iterate the available libraries in the lib folder
    std::string path = "/home/shorty/Repos/spider/bin/lib";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::cout << entry.path() << std::endl;

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

        // Assign the parameters defined in the XML config to the Module
        Assign_Module_Parameters(module);

        // Register the Module Instance
        loaded_modules.push_back(module);
    }
    return 0;
}

int Spider::Assign_Module_Parameters(Module* module)
{
    std::cout << "Parameters for Module: " << module->name << std::endl;
    pugi::xml_node module_node = modules_xml.child("modules").find_child_by_attribute("name", module->name);
    pugi::xml_node parameters_node = module_node.child("parameters");

    for (pugi::xml_node parameter : parameters_node.children()) {
                auto name = parameter.attribute("name").value();
                auto val = parameter.attribute("value").value();
                std::cout << "Parameter: " << name << " -> " <<  val;
                module->parameters.insert(std::make_pair(name,val));
                std::cout << " Registered" << std::endl;
    }

    return 0;
}