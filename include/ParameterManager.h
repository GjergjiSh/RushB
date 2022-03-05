#ifndef PARAMETERMANAGER_H
#define PARAMETERMANAGER_H

#include <pugixml.hpp>

#include "Logger.h"
#include "IModuleInterface.h"

class ParameterManager {

public:
    explicit ParameterManager(const char *modules_cfg);

    ~ParameterManager() = default;

    int Parse_Configuration();

    pugi::xml_node Get_Module_Node(const std::shared_ptr<Module> &module);

    int Assign_Module_Parameters(const std::shared_ptr<Module> &module);

    bool Module_Activated(pugi::xml_node module);

private:
    void Print_Module_Parameters(const std::shared_ptr<Module> &module);

    const char *m_modules_cfg;
    pugi::xml_document m_modules_xml;
    RBLogger::Logger m_logger;
};

#endif /* PARAMETERMANAGER_H */