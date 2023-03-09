#ifndef CAMERA_DRIVER_H
#define CAMERA_DRIVER_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <camera_status.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "cv_bridge/cv_bridge.h"
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>


class CameraDriver {
private:
    ros::NodeHandle nh;
    std::string cam_topic = "/camera/color/image_raw";
    cv_bridge::CvImage cvi_msg;
    image_transport::ImageTransport *ptrIt;
    image_transport::Publisher img_pub;

protected:
    

public:
    CameraDriver();
    ~CameraDriver();

    cv::VideoCapture input_video;
    cv::Mat frame;
    void camPublish();

};
#endif
