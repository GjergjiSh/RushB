#ifndef TF_OBJECT_DETECTOR_H
#define TF_OBJECT_DETECTOR_H

#include <tensorflow/cc/client/client_session.h>
#include <tensorflow/cc/saved_model/loader.h>
#include <tensorflow/core/framework/graph.pb.h>
#include <tensorflow/core/framework/tensor.h>
#include <tensorflow/core/graph/graph_def_builder.h>
#include <tensorflow/core/public/session.h>

#include "IObjectDetector.h"

class TfObjectDetector : public IObjectDetector {

public:
    TfObjectDetector(const char* model_path,
                     const char* label_path,
                     float confidence_threshold,
                     bool time_log);

    int Init() override;
    std::vector<DetectionUtils::tBoundingBox> Detect(cv::Mat&, bool draw);

private:
    int Init_Model() override;
    int Load_Labels() override;

    void Warmup();

    static tensorflow::Tensor Convert_Mat_To_Tensor(cv::Mat src);

    tensorflow::SavedModelBundle m_saved_model;
    tensorflow::SessionOptions m_session_options;
    tensorflow::RunOptions m_run_options;

    const std::string m_graph_input_node = "serving_default_input_tensor:0";
    std::vector<std::string> m_graph_output_nodes = {
           {"StatefulPartitionedCall:0", //detection_anchor_indices
            "StatefulPartitionedCall:1", //detection_boxes
            "StatefulPartitionedCall:2", //detection_classes
            "StatefulPartitionedCall:3", //detection_multiclass_confidences
            "StatefulPartitionedCall:4", //detection_confidences
            "StatefulPartitionedCall:5"} //num_detections
    };
};


#endif /* TF_OBJECT_DETECTOR_H */