#include "ModuleHandler.h"
#include  <chrono>

ModuleHandler::ModuleHandler(const char* modules_cfg, bool verbose)
    : m_modules_cfg(modules_cfg), m_verbose(verbose)
    {
        m_logger.Set_Name("ModuleHandler");
    }

int ModuleHandler::Init()
{
    // Init values of shared data members to 0
    memset(&m_shared_data, 0, sizeof(m_shared_data));

    // Parse the XML Configuration File
    if (Parse_Configuration() != 0) return -1;

    // Load the Modules in the lib folder
    if (Register_Modules() != 0) return -1;

    // Initialize the signal handler
    if (m_sig_handler.Init() != 0) return -1;

    // Initialize each loaded module
    auto start = std::chrono::system_clock::now();
    for (auto module : m_registered_modules) {
        try {
            if (module->Init() != 0) {
                m_logger.LOG_ERROR(std::string("Failed to initialize module: ").append(module->name));
                return -1;
            };
        }catch(std::out_of_range& oor) {
            m_logger.LOG_ERROR_DESCRIPTION(std::string("Failed to initialize module - Erronous configuration for module: ").append(module->name), oor.what());
            return -1;
        }
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    m_logger.LOG_TIME_INFO("Initialized modules in ", elapsed.count());


    m_logger.LOG_INFO("Initialization finished");
    return 0;
}

int ModuleHandler::Deinit()
{
    for (auto module : m_registered_modules) {
        module->Deinit();

        if (dlclose(module->lib_handle) != 0)
            m_logger.LOG_ERROR_DESCRIPTION("Failed to destroy module :", dlerror());
    }
    m_logger.LOG_INFO("Deinitialization finished");
    return 0;
}

// Trigger cycle for each registered module
int ModuleHandler::Run()
{
    while (!m_sig_handler.Received_Exit_Sig()) {
        for (auto module : m_registered_modules) {
            if (m_verbose) {
                // Print cycle time for each module
                auto start = std::chrono::system_clock::now();
                if (module->Cycle_Step() != 0) {
                    m_logger.LOG_ERROR_DESCRIPTION("Cycle Step failed for module: ", module->name);
                    return -1;
                };
                auto end = std::chrono::system_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                m_logger.LOG_TIME_INFO(std::string("Cycle target: ").append(module->name), elapsed.count());
            } else {
                // Trigger cycle without printing time info
                if (module->Cycle_Step() != 0) {
                    m_logger.LOG_ERROR_DESCRIPTION("Cycle Step failed for module: ", module->name);
                    return -1;
                };
            }
        }
    }

    m_logger.LOG_INFO("Exiting...");
    return 0;
}

int ModuleHandler::Parse_Configuration()
{
    // Load XML config file into memory
    pugi::xml_parse_result parse_result = m_modules_xml.load_file(m_modules_cfg);
    if (!parse_result) {
        m_logger.LOG_ERROR_DESCRIPTION("Failed to parse the modules configuration file",
                                       parse_result.description());
        return -1;
    }
    return 0;
}

int ModuleHandler::Register_Modules()
{
    auto start = std::chrono::system_clock::now();
    // Iterate the available libraries in the lib folder
    for (const auto & entry : std::filesystem::directory_iterator("./avail_modules")) {
        // Load the library
        void* lib_handle = dlopen(entry.path().c_str(), RTLD_LAZY);
        if (!lib_handle) {
            m_logger.LOG_ERROR_DESCRIPTION("Failed to load library: ", dlerror());
            return -1;
        }

        // reset errors
        dlerror();

        // load the Create Symbol of the Module
        auto Create_Module = (Create_t*)dlsym(lib_handle, "Create_Instance");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            m_logger.LOG_ERROR_DESCRIPTION("Failed to load symbol create: ", dlsym_error);
            return -1;
        }

        // Create the Module Instance
        std::shared_ptr<Module> module = Create_Module();
        module->lib_handle = lib_handle;
        module->shared_data = &m_shared_data;

        // Only register if the module is in the XML config
        pugi::xml_node module_node = m_modules_xml.child("modules").find_child_by_attribute("name", module->name.c_str());
        if (!module_node) {
            //delete module;
            continue;
        }

        // Assign the parameters defined in the XML config to the Module
        Assign_Module_Parameters(module);

        // Register the Module Instance
        m_registered_modules.push_back(module);
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    m_logger.LOG_TIME_INFO("Finished registering modules in ", elapsed.count());
    return 0;
}

int ModuleHandler::Assign_Module_Parameters(std::shared_ptr<Module> module)
{
    // Find the module's node in the XML config file
    pugi::xml_node module_node = m_modules_xml.child("modules").find_child_by_attribute("name", module->name.c_str());
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

void ModuleHandler::Print_Module_Parameters(std::shared_ptr<Module> module)
{
    for (auto parameter : module->parameters) {
        std::cout << "[" << m_logger.Time_Stamp() << "] "
                  << "\033[1;36m[I][ModuleHandler]\033[0m "
                  <<  module->name << " -> "
                  << " Parameter: " << parameter.first
                  << " Value: " << parameter.second
                  <<  std::endl;
    }
}

