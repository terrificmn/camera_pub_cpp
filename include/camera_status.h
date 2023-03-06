#ifndef CAMERA_STATUS_H
#define CAMERA_STATUS_H

#include <ros/ros.h>
#include <std_msgs/Int16.h>

enum VideoStatus {
        ACTIVE, REQUEST_STOP, STOPPED, RESTART, NORMAL_START
};

class CameraStatus {
private:
    ros::NodeHandle nh;
    ros::Subscriber sub_cam_status;

protected:
    VideoStatus video_status = VideoStatus::NORMAL_START;

public:
    CameraStatus();
    ~CameraStatus();
    
    void camStatusCb(const std_msgs::Int16::ConstPtr& msg);
    void setStatus(VideoStatus video_status);
    VideoStatus getStatus();
    
};
#endif
