#include "ModuleInterface.h"
#include "DetectionUtils.h"

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/public/session.h"

class ObjectDetector : public Module {

public:
    ObjectDetector();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

private:

    std::vector<DetectionUtils::tBoundingBox> Detect(cv::Mat&, bool draw);

    int Init_Detector();
    int Init_Model();
    int Load_Labels();

    void Warmup();

    tensorflow::Tensor Convert_Mat_To_Tensor(cv::Mat src);

    std::vector<std::string> labels;
    const char* m_model_path;
    const char* m_label_path;
    const char* estimator_config_path;
    float m_confidence_threshold;

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

    DetectionUtils::inference_time_result_t m_inference_time_result = {};
    bool m_time_log;
};