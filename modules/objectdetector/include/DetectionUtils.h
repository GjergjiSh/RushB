#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

namespace DetectionUtils {

using namespace std::chrono;

#define DRAW true
#define NO_DRAW false

typedef struct {
    double time_pre_process; // [msec]
    double time_inference; // [msec]
    double time_post_process; // [msec]
} inference_time_result_t;

typedef struct {
    int id;
    float confidence;
    cv::Rect roi; // Region of Interest
    float distance;
    std::string label;
} tBoundingBox;

typedef struct {
    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> rois; // Regions of Interest
} tPredictions;

typedef struct {
    cv::Mat instance;
    cv::Size size = cv::Size(416, 416);
    cv::Scalar mean = cv::Scalar(0, 0, 0);
    double scale = 1 / 255.0;
    bool swap_rb = false;
    bool crop = false;
} tBlob;

static void Draw_Bounding_Box(cv::Mat mat, tBoundingBox bounding_box)
{
    int baseLine;
    std::string label = cv::format("%.2f", bounding_box.confidence);
    std::string distance = cv::format("%.3f ", bounding_box.distance);

    label = bounding_box.label + " Confidence: " + label + " Distance: " + distance;

    cv::Size label_size = getTextSize(label, cv::FONT_ITALIC, 0.5, 1, &baseLine);
    int top = std::max(bounding_box.roi.y, label_size.height);

    cv::rectangle(mat,
        cv::Point(bounding_box.roi.x, bounding_box.roi.y),
        cv::Point(bounding_box.roi.x + bounding_box.roi.width,
            bounding_box.roi.y + bounding_box.roi.height),
        cv::Scalar(0, 255, 0), 4);

    rectangle(mat,
        cv::Point(bounding_box.roi.x, bounding_box.roi.y - round(1.1 * label_size.height)),
        cv::Point(bounding_box.roi.x + round(1.1 * label_size.width), top + baseLine),
        cv::Scalar(255, 255, 255), cv::FILLED);

    cv::putText(mat, label, cv::Point(bounding_box.roi.x, top), cv::FONT_ITALIC, 0.5, cv::Scalar(0, 0, 0), 1);
}

class InferenceLogger {

public:
    InferenceLogger(std::string csv_file)
        : csv_file(csv_file.append(".csv"))
    {

        this->stream.open(this->csv_file);
    }

    ~InferenceLogger() { stream.close(); }

    // This only writes the confidence and distance for a single deteciton as it is only used
    // to test the performace of the graphs in respect to a the stop sign, Must be changed to support
    // logging the detection and confidence of multiple detected objects
    int32_t Log_Inference_Time(inference_time_result_t& inference_time_result, tBoundingBox& detection)
    {
        if (stream) {
            stream << inference_time_result.time_pre_process << ","
                   << inference_time_result.time_inference << ","
                   << inference_time_result.time_post_process << ","
                   << detection.distance << ","
                   << detection.confidence << std::endl;
        } else {
            std::cout << "Inference Logger failed to write inference results to csv" << std::endl;
            return -1;
        }

        return 0;
    }

    std::ofstream stream;
    std::string csv_file;
};
}

#endif /* UTILS_H */