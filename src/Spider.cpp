#include "Spider.h"


Spider::Spider(const char* modules_cfg) : modules_cfg(modules_cfg)
{

}

Spider::~Spider()
{

}

int Spider::Init()
{
    // Load the Modules in the lib folder
    Load_Modules();

    // Initialize each loaded module
    for (auto module : loaded_modules) {
        if (module.first->Init() != 0) {
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

        module.first->Deinit();

        Destroy_t* Destroy_Module = (Destroy_t*)dlsym(module.second, "Destroy");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            LOG_ERROR_DESCRIPTION("Failed to load symbol destroy: ", dlsym_error)
        }

        Destroy_Module(module.first);

        if (dlclose(module.second) != 0) {
            LOG_ERROR_DESCRIPTION("Failed to destroy module :", dlerror());
        };
    }
    LOG_INFO("Deinitialization successful")
    return 0;
}

int Spider::Run()
{
    for (auto module : loaded_modules) {
        module.first->Cycle_Step();
    }
    return 0;
}

int Spider::Load_Modules()
{
    // Iterate the available libraries in the lib folder
    std::string path = "/home/shorty/Repos/spider/bin/lib";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::cout << entry.path() << std::endl;

        // Load the library
        void* module_handle = dlopen(entry.path().c_str(), RTLD_LAZY);
        if (!module_handle) {
            LOG_ERROR_DESCRIPTION("Failed to load library: ", dlerror());
            return -1;
        }

        // reset errors
        dlerror();

        // load the Create Symbol of the Module
        Create_t* Create_Module = (Create_t*)dlsym(module_handle, "Create");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            LOG_ERROR_DESCRIPTION("Failed to load symbol create: ", dlsym_error)
            return -1;
        }

        // Create the Module Instance
        Module* module = Create_Module();

        // Register the Module Instance
        loaded_modules.insert(std::make_pair(module, module_handle));
    }
    return 0;
}

int Spider::Register_Modules()
{
    Load_Modules();

    return 0;
}

int Spider::Configure_Modules()
{
    // Parse the modules configuration file
    pugi::xml_document modules_xml;
    pugi::xml_parse_result parse_result = modules_xml.load_file(modules_cfg);
    if (!parse_result) {
        LOG_ERROR_DESCRIPTION("Failed to parse the modules configuration file",
            parse_result.description());
        return -1;
    }

    std::unordered_map<std::string, std::string> module_parameters;

    // Iterate through each module
    pugi::xml_node modules = modules_xml.child("modules");
    for (pugi::xml_node module : modules) {
        // Iterate through a single modules parameters
        std::cout << "Module: " << module.attribute("name").value() << std::endl;
        pugi::xml_node parameters = module.child("parameters");
            for (pugi::xml_node parameter : parameters.children()) {
                std::cout << parameter.attribute("name").value() << parameter.attribute("value").value() << std::endl;
                // Register the parameters
                module_parameters.emplace(std::make_pair(parameter.attribute("name").value(), parameter.attribute("value").value()));
            }

        // Note: Not sure if this actually deletes all the elements of the map because they are pointers
        module_parameters.clear();

    }
    return 0;
}