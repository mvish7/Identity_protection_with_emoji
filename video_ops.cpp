//
// Created by flying-dutchman on 09.08.20.
//

#include "video_ops.h"

using namespace cv;
using namespace cv::dnn;
using namespace std;

cv::dnn::Net read_net(const std::string& model_config, const std::string& model_weights)
{
    Net net = readNetFromTensorflow(model_weights, model_config);
    return net;
}


cv::Mat detect_faces(cv::dnn::Net& net, cv::Mat& curr_frame)
{
    const double scale_factor = 1.0;
    const cv::Scalar mean_val = (104, 177, 123);
    cv::Size frame_size = cv::Size(curr_frame.rows, curr_frame.cols);
    cv::Mat img_blob = cv::dnn::blobFromImage(curr_frame, scale_factor, frame_size, mean_val, true, false);

    net.setInput(img_blob, "data");
    cv::Mat detections = net.forward("detection_out");

    return detections;
}