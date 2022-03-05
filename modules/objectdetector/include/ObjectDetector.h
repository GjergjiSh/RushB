#include "IModuleInterface.h"
#include "IObjectDetector.h"
#include "TfObjectDetector.h"
#include "DnnObjectDetector.h"


class ObjectDetector : public Module {

public:
    ObjectDetector();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

private:
    std::shared_ptr<IObjectDetector> detector;
    int m_input_image_height;
    int m_input_image_width;
};