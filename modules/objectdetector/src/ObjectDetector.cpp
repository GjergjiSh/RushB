#include "ObjectDetector.h"

ObjectDetector::ObjectDetector() {
    name="ObjectDetector";
    logger.Set_Name(name);
}

int ObjectDetector::Init()
{
    m_input_image_height = std::stoi(parameters.at("INPUT_IMAGE_HEIGHT"));
    m_input_image_width = std::stoi(parameters.at("INPUT_IMAGE_WIDTH"));

    std::string detector_type = parameters.at("DETECTOR_TYPE");

    if (detector_type == "TF") {
        logger.Info("Initializing TensorFlow Object Detector");

        detector = std::make_shared<TfObjectDetector>(
            parameters.at("SAVED_MODEL_DIR").c_str(),
            parameters.at("LABEL_PATH").c_str(),

            std::stof(parameters.at("CONFIDENCE_THRESHOLD")),
            std::stoi(parameters.at("TIME_LOG")));

    } else if (detector_type == "DNN") {
        logger.Info("Initializing OpenCV DNN Object Detector");

        detector = std::make_shared<DnnObjectDetector>(
            parameters.at("YOLO_CFG_PATH").c_str(),
            parameters.at("YOLO_WEIGHTS_PATH").c_str(),
            parameters.at("LABEL_PATH").c_str(),

            std::stof(parameters.at("CONFIDENCE_THRESHOLD")),
            std::stof(parameters.at("NMS_THRESHOLD")),
            std::stoi(parameters.at("TIME_LOG")));

    } else {
        logger.Error("Invalid parameter for detector type. Accepted Values: TF, DNN");
        return -1;
    }

    detector->m_logger = &logger;
    return detector->Init();
}

int ObjectDetector::Cycle_Step()
{
    cv::Mat frame = cv::Mat(m_input_image_height, m_input_image_width, CV_8UC3, (void*)shared_data->video.frame);
    if (frame.data) {
        std::vector<DetectionUtils::tBoundingBox> results = detector->Detect(frame, DRAW);
    }
    return 0;
}

int ObjectDetector::Deinit() {
    return 0;
}

// Factory Methods
Module *Create_Instance() {
    return new ObjectDetector;
}

void Destroy_Instance(Module *module) {
    delete module;
}
