#include "IModuleInterface.h"

class Reader : public Module {

public:
    Reader();

    int Init() override;
    int Cycle_Step() override;
    int Deinit() override;
};