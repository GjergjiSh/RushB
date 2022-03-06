#include "ModuleManager.h"
#include "cassert"

ModuleManager::ModuleManager(const char* modules_cfg, bool verbose)
    : m_verbose(verbose)
{
    m_logger.Set_Name("ModuleManager");
    m_parameter_manager = std::make_unique<ParameterManager>(modules_cfg);
    m_shared_data = { 0 };
}

int ModuleManager::Init()
{
    // Init values of shared data members to 0
    memset(&m_shared_data, 0, sizeof(m_shared_data));

    // Initialize the signal handler
    if (m_sig_handler.Init() != 0)
        return -1;

    // Parse the XML Configuration File
    if (m_parameter_manager->Load_Configuration() != 0)
        return -1;

    // Load the Modules in the lib folder
    if (Register_Modules() != 0)
        return -1;

    m_logger.Info("Initialization finished");
    return 0;
}

int ModuleManager::Init_Module(Module* const& module)
{

    m_logger.Info(std::string("Initializing: ").append(module->name));

    auto start = std::chrono::system_clock::now();

    try {
        if (module->Init() != 0) {
            m_logger.Error(std::string("Failed to initialize module: ")
                    .append(module->name));

            return -1;
        }
    } catch (std::out_of_range& oor) {
        m_logger.Error_Description(
            std::string("Failed to initialize module - Invalid configuration for module: ")
                .append(module->name),
                oor.what());

        return -1;
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    m_logger.Time_Info(module->name.append(" initialized in "),
        (int)elapsed.count());

    return 0;
}

int ModuleManager::Deinit()
{
    for (const auto& module : m_registered_modules) {
        module->Deinit();
        Destroy_Module(module->lib_handle, module);
    }

    m_logger.Info("Deinitialization finished");
    return 0;
}

// Trigger cycle for each registered module
int ModuleManager::Run()
{
    while (!SignalHandler::Received_Exit_Sig()) {
        for (const auto& module : m_registered_modules) {
            if (m_verbose) {
                // Print cycle time for each module
                auto start = std::chrono::system_clock::now();
                if (Cycle_Module(module) != 0) return -1;
                auto end = std::chrono::system_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                m_logger.Time_Info(std::string("Cycle target: ")
                                       .append(module->name),
                                        (int)elapsed.count());

            } else if (Cycle_Module(module) != 0) {
                return -1;
            }
        }
        // usleep(100000);
    }

    m_logger.Info("Exiting...");
    return 0;
}

int ModuleManager::Cycle_Module(Module* const& module)
{
    if (module->Cycle_Step() != 0) {
        m_logger.Error_Description("Cycle Step failed for module: ", module->name);
        return -1;
    }
    return 0;
}

int ModuleManager::Register_Modules()
{
    auto start = std::chrono::system_clock::now();
    // Iterate the available libraries in the lib folder
    for (const auto& entry : std::filesystem::directory_iterator("./avail_modules")) {
        void* lib_handle = Get_Module_Handle(entry);
        if (!lib_handle) return -1;

        // reset errors
        dlerror();

        Module* module = Create_Module(lib_handle);

        // Only init and register if the module is in the XML config
        if (m_parameter_manager->Module_Activated(m_parameter_manager->Get_Module_Node(module))) {

            // Assign the parameters defined in the XML config to the Module
            m_parameter_manager->Assign_Module_Parameters(module);
            // Initialize the module
            if (Init_Module(module) != 0) return -1;
            // Register the Module Instance
            m_registered_modules.push_back(module);

        } else {
            Destroy_Module(lib_handle, module);
        }
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    m_logger.Time_Info("Finished registering modules in ", (int)elapsed.count());
    return 0;
}

void* ModuleManager::Get_Module_Handle(const std::filesystem::directory_entry& entry)
{
    // Load the library
    void* lib_handle = dlopen(entry.path().c_str(), RTLD_LAZY);
    if (!lib_handle) {
        m_logger.Error_Description("Failed to load library: ", dlerror());
    }
    return lib_handle;
}

void ModuleManager::Destroy_Module(void* lib_handle, Module* module)
{
    Destroy_t* Destroy_Module = Get_Destroy_Symbol(lib_handle);

    // Destructor and delete delegated to the module's factory method
    if (Destroy_Module)
        Destroy_Module(module);
    else
        m_logger.Warning(std::string("Will not be able to destroy: ")
                             .append(module->name));

    if (lib_handle) {
        if (dlclose(module->lib_handle) != 0)
            m_logger.Warning(std::string("Failed to unload library for module :")
                                .append(module->name + dlerror()));
    }
}

Module* ModuleManager::Create_Module(void* lib_handle)
{
    // load the factory method of the Module
    Create_t* Create_Module = Get_Create_Symbol(lib_handle);

    // Create the Module Instance
    // Constructor Delegated to the module's factory method
    Module* module = Create_Module();
    module->lib_handle = lib_handle;
    module->shared_data = &m_shared_data;
    return module;
}

Create_t* ModuleManager::Get_Create_Symbol(void* lib_handle)
{
    auto Create_Module = (Create_t*)dlsym(lib_handle, "Create_Instance");
    const char* dlsym_error = dlerror();

    if (dlsym_error) {
        m_logger.Error_Description("Failed to load symbol create: ", dlsym_error);
    }

    return Create_Module;
}

Destroy_t* ModuleManager::Get_Destroy_Symbol(void* lib_handle)
{
    auto Create_Module = (Destroy_t*)dlsym(lib_handle, "Destroy_Instance");
    const char* dlsym_error = dlerror();

    if (dlsym_error) {
        m_logger.Warning(std::string("Failed to load the destroy symbol: ")
                             .append(dlsym_error));
    }

    return Create_Module;
}
