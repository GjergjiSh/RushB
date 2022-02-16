#include "Module.h"

class Reader : public Module {

public:
    Reader();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;
};