#include "ObjectDetector.h"

ObjectDetector::ObjectDetector() {
    this->name="ObjectDetector";
}

int ObjectDetector::Init()
{
    LOG_INFO("Initializing...");
    return Init_Detector();
}

int ObjectDetector::Cycle_Step()
{
    cv::Mat frame = cv::Mat(480, 640, CV_8UC3, (void *)this->shared_data->video.frame);
    std::scoped_lock<std::mutex> lock(mtx);
    std::vector<DetectionUtils::tBoundingBox> results = Detect(frame, DRAW);
    return 0;
}

int ObjectDetector::Deinit()
{
    LOG_INFO("Deinitializing...");
    return 0;
}

/**************************************************************************************
 * @note: We still need to find a way to get the total nr of predicted boxes
 *************************************************************************************/
std::vector<DetectionUtils::tBoundingBox> ObjectDetector::Detect(cv::Mat& src, bool draw)
{
    //Preprocess
    auto time_preprocess0 = std::chrono::steady_clock::now();
    std::vector<DetectionUtils::tBoundingBox> detections;
    tensorflow::Tensor input = Convert_Mat_To_Tensor(src);
    std::vector<std::pair<std::string, tensorflow::Tensor>> graph_input = { { graph_input_node, input } };
    std::vector<tensorflow::Tensor> graph_output;
    int height = src.rows;
    int width = src.cols;
    auto time_preprocess1 = std::chrono::steady_clock::now();

    //Run Inference
    auto time_inference0 = std::chrono::steady_clock::now();
    this->saved_model.GetSession()->Run(graph_input, graph_output_nodes, {}, &graph_output);
    auto time_inference1 = std::chrono::steady_clock::now();


    //Postprocess: Get the output at the out nodes
    auto time_post_process0 = std::chrono::steady_clock::now();
    auto predicted_boxes = graph_output[1].tensor<float, 3>();
    auto predicted_confidences = graph_output[4].tensor<float, 2>();
    auto predicted_labels = graph_output[2].tensor<float, 2>();
    //auto num_detections = graph_output[5].tensor<float, 1>();
    int nr_of_predictions = 50;//(int)num_detections.NumIndices;

    //detections.reserve(nr_of_predictions);

    for (int i = 0; i < nr_of_predictions; i++) {
        DetectionUtils::tBoundingBox bounding_box;

        bounding_box.confidence = predicted_confidences(0, i);
        if (bounding_box.confidence > confidence_threshold) {

            bounding_box.roi.y = (int)(predicted_boxes(0, i, 0) * height);
            bounding_box.roi.x = (int)(predicted_boxes(0, i, 1) * width);
            bounding_box.roi.height = (int)(predicted_boxes(0, i, 2) * height) - bounding_box.roi.y;
            bounding_box.roi.width = (int)(predicted_boxes(0, i, 3) * width) - bounding_box.roi.x;

            //#Note: Id indexing starts form 1
            bounding_box.id = predicted_labels(0, i);
            bounding_box.label = labels[bounding_box.id-1];

            detections.push_back(bounding_box);

            // If drawing is active, draw the bounding box on the frame
            if (draw)
                DetectionUtils::Draw_Bounding_Box(src, bounding_box);
        }
    }
    auto time_post_process1 = std::chrono::steady_clock::now();

    //Calculate inference time results for the last frame: pre,during and post processing
    this->inference_time_result.time_post_process = (time_post_process1 - time_post_process0).count() / 1000000.0;
    this->inference_time_result.time_inference = (time_inference1 - time_inference0).count() / 1000000.0;
    this->inference_time_result.time_pre_process = (time_preprocess1 - time_preprocess0).count() / 1000000.0;

    return detections;
}

int ObjectDetector::Load_Labels()
{
    std::ifstream labels_file(this->label_path);
    std::string label;

    if (labels_file) {
        while (getline(labels_file, label)) {
            this->labels.emplace_back(label);
        }
        LOG_INFO(std::string("Loaded labels from: ").append(this->label_path));
    } else {
        LOG_ERROR("Failed to load labels");
        return -1;
    }
    return 0;
}

int ObjectDetector::Init_Model()
{
    session_options.config.mutable_gpu_options()->set_allow_growth(true);

    // Parse saved model directory and create the neural network
    tensorflow::Status status = tensorflow::LoadSavedModel(
                                this->session_options,
                                this->run_options,
                                this->model_path,
                                { "serve" },
                                &this->saved_model);

    // Make sure the GPU is visible
    setenv("CUDA_VISIBLE_DEVICES", "0,1", -1);

    if (!status.ok()) {
        LOG_ERROR("Failed to load model");
        return -1;
    }

    // Print Device Info
    std::vector<tensorflow::DeviceAttributes> response;
    saved_model.GetSession()->ListDevices(&response);

    for (int index = 0; index < response.size(); ++index) {
        auto value = response[index];
        std::cout << "[I][ObjectDetector] Available device: "
                  << index << "  "
                  << response[index].name()
                  << std::endl;
    }

    return 0;
}

int ObjectDetector::Init_Detector()
{
    model_path = parameters.at("MODEL_PATH").c_str();
    label_path = parameters.at("LABEL_PATH").c_str();
    confidence_threshold = std::stof(parameters.at("CONFIDENCE_THRESHOLD"));

    if (Init_Model() != 0) return -1;
    if (Load_Labels() != 0) return -1;

    return 0;
}

// Convert a frame into a tensor. Note that this becomes much slower on high resolution images, Naive OpenMP
// parallelization helps but only a little bit. It is possible to gain much higher performance gains if the
// routine is delegated to the GPU with OpenCL/CUDA
tensorflow::Tensor ObjectDetector::Convert_Mat_To_Tensor(cv::Mat src)
{
    int height = src.rows;
    int width = src.cols;
    int cnls = src.channels();

    tensorflow::Tensor input_tensor(tensorflow::DT_UINT8, tensorflow::TensorShape({ 1, height, width, cnls }));
    auto mapped_input_tensor = input_tensor.tensor<tensorflow::uint8, 4>();

    cv::Mat conversion;
    src.convertTo(conversion, CV_8UC3);
    const tensorflow::uint8* source_data = (tensorflow::uint8*)conversion.data;

#pragma omp for
    for (int y = 0; y < height; y++) {
        const tensorflow::uint8* source_row = source_data + (y * width * cnls);
        for (int x = 0; x < width; x++) {
            const tensorflow::uint8* source_pixel = source_row + (x * cnls);
            for (int c = 0; c < cnls; c++) {
                const tensorflow::uint8* source_value = source_pixel + c;
                mapped_input_tensor(0, y, x, c) = *source_value;
            }
        }
    }
    return input_tensor;
}

extern "C" Module* Create() { return new ObjectDetector;}
extern "C" void Destroy(Module* module) {delete module;}