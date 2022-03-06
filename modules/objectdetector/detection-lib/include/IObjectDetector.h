#ifndef IOBJECT_DETECTOR_H
#define IOBJECT_DETECTOR_H

#include "DetectionUtils.h"
#include "Logger.h"

class IObjectDetector {

public:
    ~IObjectDetector() = default;

    virtual std::vector<DetectionUtils::tBoundingBox> Detect(cv::Mat&, bool draw) = 0;
    virtual int Init() = 0;
    virtual int Init_Model() = 0;
    virtual int Load_Labels() = 0;

    const char* m_model_path;
    const char* m_label_path;
    float m_confidence_threshold;
    bool m_time_log;
    std::vector<std::string> m_labels;
    RBLogger::Logger* m_logger;
    DetectionUtils::inference_time_result_t m_inference_time_result = {};
};

#endif /* IOBJECT_DETECTOR_H */