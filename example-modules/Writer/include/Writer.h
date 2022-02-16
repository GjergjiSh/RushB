#include "Module.h"

class Writer : public Module {

public:
    Writer();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;
};