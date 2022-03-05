#ifndef DNN_OBJECT_DETECTOR_H
#define DNN_OBJECT_DETECTOR_H

#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/dnn/dnn.hpp>

#include "IObjectDetector.h"

class DnnObjectDetector : public IObjectDetector {
public:
    DnnObjectDetector(const char* model_path,
        const char* labels_path,
        const char* weights_path,
        float confidence_threshold,
        float nms_threshold,
        bool time_log);

    int Init() override;
    std::vector<DetectionUtils::tBoundingBox> Detect(cv::Mat&, bool draw) override;

private:
    int Init_Model() override;
    int Load_Labels() override;

    void Get_Output_Layer_Names();
    std::vector<cv::Mat> Invoke_Graph(cv::Mat mat);
    DetectionUtils::tPredictions Get_Confident_Predictions(cv::Mat& mat, std::vector<cv::Mat>& net_output);
    std::vector<DetectionUtils::tBoundingBox> Perform_NMS(cv::Mat& mat, DetectionUtils::tPredictions& predictions, bool draw);

    cv::dnn::Net m_neural_net;

    std::vector<cv::String> m_output_layer_names;

    float m_nms_threshold;
    const char* m_weights_path;
};

#endif /* DNN_OBJECT_DETECTOR_H */