#include "ModuleInterface.h"
#include "DetectionUtils.h"
#include <mutex>

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/public/session.h"

#define LOG_INFO(msg) \
    std::cout << "[I][ObjectDetector] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][ObjectDetector] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][ObjectDetector] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][ObjectDetector] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][ObjectDetector] " << msg << std::endl;

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

    tensorflow::Tensor Convert_Mat_To_Tensor(cv::Mat src);

    std::vector<std::string> labels;
    const char* model_path;
    const char* label_path;
    const char* estimator_config_path;
    float confidence_threshold;

    tensorflow::SavedModelBundle saved_model;
    tensorflow::SessionOptions session_options;
    tensorflow::RunOptions run_options;

    const std::string graph_input_node = "serving_default_input_tensor:0";
    std::vector<std::string> graph_output_nodes = {
        {   "StatefulPartitionedCall:0", //detection_anchor_indices
            "StatefulPartitionedCall:1", //detection_boxes
            "StatefulPartitionedCall:2", //detection_classes
            "StatefulPartitionedCall:3", //detection_multiclass_confidences
            "StatefulPartitionedCall:4", //detection_confidences
            "StatefulPartitionedCall:5" } //num_detections
    };

    DetectionUtils::inference_time_result_t inference_time_result = {};

    std::mutex mtx;
};