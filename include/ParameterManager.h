#ifndef PARAMETERMANAGER_H
#define PARAMETERMANAGER_H

#include <pugixml.hpp>

#include "IModuleInterface.h"
#include "Logger.h"

class ParameterManager {

public:
    explicit ParameterManager(const char* modules_cfg);
    ~ParameterManager() = default;

    int Load_Configuration();
    pugi::xml_node Get_Module_Node(const Module* module);
    int Assign_Module_Parameters(Module* module);
    bool Module_Activated(pugi::xml_node module);

private:
    void Print_Module_Parameters(const Module* module);

    const char* m_modules_cfg;
    pugi::xml_document m_modules_xml;
    RBLogger::Logger m_logger;
};

#endif /* PARAMETERMANAGER_H */