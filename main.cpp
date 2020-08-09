#include <iostream>
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

    VideoCapture vid_cap("../videoplayback.mp4");
    if (!vid_cap.isOpened())
    {
        throw std::logic_error("Error reading the video file");
        return -1;
    }
    vid_cap.set(CAP_PROP_FPS, 10);


    while(1)
    {
        Mat frame;
        vid_cap >> frame;
        if (frame.empty())
            break;
        imshow("Video Display", frame);

        char c = (char)waitKey(25);
        if (c==27)
            break;
    }

    vid_cap.release();
    destroyAllWindows();
    return 0;
}
