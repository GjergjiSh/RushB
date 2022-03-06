#include "IModuleInterface.h"
#include "Logger.h"

class TEMPLATE : public Module {

public:
    TEMPLATE();

    int Init() override;
    int Cycle_Step() override;
    int Deinit() override;

private:
};