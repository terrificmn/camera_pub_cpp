#include <camera_status.h>

CameraStatus::CameraStatus() {
    ROS_INFO("Camera Status Init");
    sub_cam_status = nh.subscribe<std_msgs::Int16>("/camera_status", 10, &CameraStatus::camStatusCb, this);
}

CameraStatus::~CameraStatus() {} 

void CameraStatus::camStatusCb(const std_msgs::Int16::ConstPtr& msg) {
    if(msg->data == VideoStatus::REQUEST_STOP) {
        ROS_INFO("REQUESTED STOP!!!");
        this->setStatus(VideoStatus::REQUEST_STOP);
    } else if(msg->data == VideoStatus::RESTART) {
        ROS_INFO("RESTART!!!");
        this->setStatus(VideoStatus::RESTART);
    }
}

void CameraStatus::setStatus(VideoStatus video_status) {
    this->video_status = video_status;
} 

VideoStatus CameraStatus::getStatus() {
    return this->video_status;
}