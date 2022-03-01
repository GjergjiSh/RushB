#include "ParameterManager.h"

ParameterManager::ParameterManager(const char* modules_cfg) : m_modules_cfg(modules_cfg)
{
    m_logger.Set_Name("ParameterManager");
}

// Load XML config file into memory
int ParameterManager::Parse_Configuration()
{
    pugi::xml_parse_result parse_result = m_modules_xml.load_file(m_modules_cfg);
    if (!parse_result) {
        m_logger.Error_Description("Failed to parse the modules configuration file",
                                   parse_result.description());
        return -1;
    }
    return 0;
}

// Convencience method for retrieving the a module's xml node in the module config
pugi::xml_node ParameterManager::Get_Module_Node(std::shared_ptr<Module> module)
{
    pugi::xml_node module_node = m_modules_xml.child("modules")
                                              .find_child_by_attribute(
                                              "name",module->name.c_str());

    if (!module_node) {
        m_logger.Warning("Module not found");
    }

    return module_node;
}

// Assign the parameters defined in the XML config to the Module
int ParameterManager::Assign_Module_Parameters(std::shared_ptr<Module> module)
{
    // Find the module's node in the XML config file
    pugi::xml_node module_node = Get_Module_Node(module);

    if (!module_node) return -1;

    pugi::xml_node parameters_node = module_node.child("parameters");

    if (!parameters_node) return -1;

    // Assign the parameter names and values to the module
    for (pugi::xml_node parameter : parameters_node.children()) {
        auto name = parameter.attribute("name").value();
        auto val = parameter.attribute("value").value();
        module->parameters.insert(std::make_pair(name, val));
    }

    // Print the assigned configuration
    Print_Module_Parameters(module);

    return 0;
}

// Print the assigned configuration
void ParameterManager::Print_Module_Parameters(std::shared_ptr<Module> module)
{
        for (auto parameter : module->parameters) {
        std::cout << "[" << m_logger.Time_Stamp() << "] "
                  << "\033[1;32m[I][ParameterManager]\033[0m "
                  <<  module->name << " -> "
                  << " Parameter: " << parameter.first
                  << " Value: " << parameter.second
                  <<  std::endl;
    }
}