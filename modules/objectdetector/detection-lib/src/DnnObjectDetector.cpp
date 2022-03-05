#include "DnnObjectDetector.h"

DnnObjectDetector::DnnObjectDetector(const char* model_path,
    const char* labels_path,
    const char* weights_path,
    float confidence_threshold,
    float nms_threshold,
    bool time_log)
{
    m_model_path = model_path;
    m_label_path = labels_path;
    m_weights_path = weights_path;
    m_confidence_threshold = confidence_threshold;
    m_nms_threshold = nms_threshold;
    m_time_log = time_log;
}

std::vector<DetectionUtils::tBoundingBox> DnnObjectDetector::Detect(cv::Mat& src, bool draw)
{
    DetectionUtils::tPredictions predictions;
    std::vector<DetectionUtils::tBoundingBox> bounding_boxes;
    std::vector<cv::Mat> net_output;

    // Run inference
    net_output = Invoke_Graph(src);

    auto time_post_process0 = std::chrono::steady_clock::now();
    // Eliminate the predictions with low confidence scores
    predictions = Get_Confident_Predictions(src, net_output);
    // Remove duplicate boxes for the same object and draw the Detections on the input frame
    bounding_boxes = Perform_NMS(src, predictions, draw);
    auto time_post_process1 = std::chrono::steady_clock::now();

    m_inference_time_result.time_post_process = (time_post_process1 - time_post_process0).count() / 1000000.0;

    return bounding_boxes;
}

// Get all of the detected objects for which the confidence is higher than the configured threshhold
DetectionUtils::tPredictions DnnObjectDetector::Get_Confident_Predictions(cv::Mat& img, std::vector<cv::Mat>& net_output)
{
    DetectionUtils::tPredictions predictions;
    cv::Point class_id;
    double confidence;
    cv::Rect box;
    int cx, cy;

    for (size_t i = 0; i < net_output.size(); ++i) {

        float* data = (float*)net_output[i].data;
        for (int j = 0; j < net_output[i].rows; ++j, data += net_output[i].cols) {

            cv::Mat scores = net_output[i].row(j).colRange(5, net_output[i].cols);
            cv::minMaxLoc(scores, 0, &confidence, 0, &class_id);

            if (confidence > m_confidence_threshold) {
                cx = (int)(data[0] * img.cols);
                cy = (int)(data[1] * img.rows);
                box.width = (int)(data[2] * img.cols);
                box.height = (int)(data[3] * img.rows);
                box.x = cx - box.width / 2;
                box.y = cy - box.height / 2;
                predictions.rois.push_back(box);
                predictions.class_ids.push_back(class_id.x);
                predictions.confidences.push_back((float)confidence);
            }
        }
    }
    return predictions;
}

// Remove duplicate bounding boxes for the detected objects (Draw decides if the boxes are drawn )
std::vector<DetectionUtils::tBoundingBox> DnnObjectDetector::Perform_NMS(cv::Mat& img, DetectionUtils::tPredictions& predictions, bool draw)
{
    std::vector<int> indices;
    std::vector<DetectionUtils::tBoundingBox> detections;
    cv::dnn::NMSBoxes(predictions.rois, predictions.confidences,m_confidence_threshold, m_nms_threshold, indices);

    for (auto it = indices.begin(); it != indices.end(); ++it) {
        DetectionUtils::tBoundingBox bounding_box;
        //#Note: Adding one to the bounding box id to start indexing at 1
        //This is to be consistent with the Tensorflow Object Detector
        bounding_box.id = predictions.class_ids[*it] + 1;
        bounding_box.roi = predictions.rois[*it];
        bounding_box.confidence = predictions.confidences[*it];
        bounding_box.label = m_labels[bounding_box.id - 1];

        detections.push_back(bounding_box);
        if (draw)
            DetectionUtils::Draw_Bounding_Box(img, bounding_box);
    }
    return detections;
}

// Confiugre the dnn (weights,cfg,backend,cpu/gpu)
int32_t DnnObjectDetector::Init_Model()
{
    m_neural_net = cv::dnn::readNetFromDarknet(m_model_path, m_weights_path);

    if (m_neural_net.empty()) {
        m_logger->Error("Failed to initialize model");
        return -1;
    } else {
        m_logger->Info(std::string("Loaded model from: ").append(m_model_path));
    }

    // These are automatically set to OpenCV and CPU if a cuda device
    // isn't found or OpenCV was not built with cuda support
    m_neural_net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    m_neural_net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

    cv::cuda::printShortCudaDeviceInfo(cv::cuda::getDevice());
    int cuda_devices_number = cv::cuda::getCudaEnabledDeviceCount();
    if (cuda_devices_number = 0)
        m_logger->Warning("No cuda enabled devices found");

    cv::cuda::DeviceInfo device_info;
    bool is_device_compatible = device_info.isCompatible();
    if (is_device_compatible)
        m_logger->Info(std::string("CUDA Device Number: ")
                       .append(std::to_string(cuda_devices_number)));
    else
        m_logger->Warning("No cuda compatible devices found");

    return 0;
}

int DnnObjectDetector::Load_Labels()
{
    std::ifstream labels_file(m_label_path);
    std::string label;

    if (labels_file) {
        while (getline(labels_file, label)) {
            m_labels.emplace_back(label);
        }
        m_logger->Info(std::string("Loaded labels from: ").append(m_label_path));
    } else {
        m_logger->Error("Failed to load labels");
        return -1;
    }
    return 0;
}

int32_t DnnObjectDetector::Init()
{
    if (Init_Model() != 0) return -1;
    if (Load_Labels() != 0) return -1;;

    Get_Output_Layer_Names();
    return 0;
}

// Get the output layer names of the dnn (The last layers of the network -> Output of the dnn)
void DnnObjectDetector::Get_Output_Layer_Names()
{
    std::vector<int> output_layers = m_neural_net.getUnconnectedOutLayers();
    std::vector<cv::String> layer_names = m_neural_net.getLayerNames();
    m_output_layer_names.resize(output_layers.size());
    for (size_t i = 0; i < output_layers.size(); ++i) {
        m_output_layer_names[i] = layer_names[output_layers[i] - 1];
    }
}

// Input a frame into the dnn and retreive the output of the dnn
std::vector<cv::Mat> DnnObjectDetector::Invoke_Graph(cv::Mat img)
{
    auto time_preprocess0 = std::chrono::steady_clock::now();
    std::vector<cv::Mat> net_output;
    DetectionUtils::tBlob blob;
    cv::dnn::blobFromImage(img, blob.instance, blob.scale, blob.size, blob.mean, blob.swap_rb, blob.crop);
    m_neural_net.setInput(blob.instance);
    auto time_preprocess1 = std::chrono::steady_clock::now();
    auto time_inference0 = std::chrono::steady_clock::now();

    m_neural_net.forward(net_output, m_output_layer_names);
    auto time_inference1 = std::chrono::steady_clock::now();

    m_inference_time_result.time_inference = (time_inference1 - time_inference0).count() / 1000000.0;
    m_inference_time_result.time_pre_process = (time_preprocess1 - time_preprocess0).count() / 1000000.0;

    return net_output;
}