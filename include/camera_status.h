#ifndef CAMERA_STATUS_H
#define CAMERA_STATUS_H

#include <ros/ros.h>
#include <std_msgs/Int16.h>

enum VideoStatus {
    ACTIVE, REQUEST_STOP, STOPPED, CAMERA_START, INACTIVE
};

class CameraStatus {
private:
    ros::NodeHandle nh;
    ros::Subscriber sub_cam_status;

protected:
    VideoStatus video_status = VideoStatus::INACTIVE;
    bool is_camera_running = false;
    ros::Time start_time;
    ros::Duration duration_time;

public:
    CameraStatus();
    ~CameraStatus();
    
    void camStatusCb(const std_msgs::Int16::ConstPtr& msg);
    void setStatus(VideoStatus video_status);
    VideoStatus getStatus();
    
    void setIsCameraRunning(bool running_state);
    bool getIsCameraRunning();

    void setCameraStartTime();
    void calculateActiveTime();
    double getDurationTime(); 
};
#endif
