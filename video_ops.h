//
// Created by flying-dutchman on 09.08.20.
//
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>

#ifndef IDENTITY_PROTECTION_VIDEO_OPS_H
#define IDENTITY_PROTECTION_VIDEO_OPS_H

cv::dnn::Net read_net(const std::string& model_config, const std::string& model_weights);
cv::Mat detect_faces(cv::dnn::Net& net, cv::Mat& curr_frame);

#endif //IDENTITY_PROTECTION_VIDEO_OPS_H
