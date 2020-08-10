#include "video_ops.h"
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
//    if(argc<1)
//    {
//        std::cout<<"Please enter the name of video file";
//    }
    float conf = 0.5;
    const std::string model_config = "../model_files/opencv_face_detector.pbtxt";
    const std::string model_weights = "../model_files/opencv_face_detector_uint8.pb";
    std::string emoji_path = "../emoji_set/";

    std::vector<Mat> emoji_set;
    std::vector<String> emoji_names;

    glob(emoji_path.append("*.png"), emoji_names, false);
    size_t img_num = emoji_names.size();

    for(size_t cnt= 0; cnt<img_num; cnt++)
    {
        emoji_set.push_back(imread(emoji_names[cnt]));
    }

    cv::dnn::Net net = read_net(model_config, model_weights);

    VideoCapture vid_cap("../videoplayback.mp4");
    if (!vid_cap.isOpened())
    {
        throw std::logic_error("Error reading the video file");
        return -1;
    }
    //vid_cap.set(CAP_PROP_FPS, 10);


    while(1)
    {
        Mat frame;
        vid_cap >> frame;
        if (frame.empty())
            break;
        cv::Mat detections = detect_faces(net, frame);
        cv::Mat detection_details (detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

        for(int i = 0; i < detection_details.rows; i++)
        {
            float confidence = detection_details.at<float>(i, 2);
            if(confidence > conf)
            {
                int x1 = int(detection_details.at<float>(i, 3) * frame.cols);
                int y1 = int(detection_details.at<float>(i, 4) * frame.rows);
                int x2 = int(detection_details.at<float>(i, 5) * frame.cols);
                int y2 = int(detection_details.at<float>(i, 6) * frame.rows);
                cv::rectangle(frame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0),2, 4);
            }
        }

        imshow("Video Display", frame);
        char c = (char)waitKey(25);
        if (c==27)
            break;
    }

    vid_cap.release();
    destroyAllWindows();
    return 0;
}
