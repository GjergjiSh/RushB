#include "IModuleInterface.h"

class Writer : public Module {

public:
    Writer();

    int Init() override;
    int Cycle_Step() override;
    int Deinit() override;
};