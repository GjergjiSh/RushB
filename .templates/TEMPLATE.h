#include "ModuleInterface.h"
#include "Logger.h"

class TEMPLATE : public Module {

public:
    TEMPLATE();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

private:
};