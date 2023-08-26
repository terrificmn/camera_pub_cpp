#include <camera_status.h>

CameraStatus::CameraStatus() {
    ROS_INFO("Camera Status Init");
    sub_cam_status = nh.subscribe<std_msgs::Int16>("/camera_request", 10, &CameraStatus::camStatusCb, this);
}

CameraStatus::~CameraStatus() {} 

void CameraStatus::camStatusCb(const std_msgs::Int16::ConstPtr& msg) {
    if(msg->data == VideoStatus::REQUEST_STOP) {
        if(this->is_camera_running) {
            ROS_INFO("[Subscribed] Received a STOP msg");
            this->setStatus(VideoStatus::REQUEST_STOP);
        } else {
            ROS_WARN("already stopped");
        }
    } else if(msg->data == VideoStatus::CAMERA_START) {
        if(!this->is_camera_running) {
            ROS_INFO("[Subscribed] Received a START msg");
            this->setStatus(VideoStatus::CAMERA_START);
        } else {
            ROS_WARN("NOT allowed to start twice");
        }
    } else {
        ROS_ERROR("Not supported. This will be ignored");
    }
}

void CameraStatus::setStatus(VideoStatus video_status) {
    this->video_status = video_status;
} 

VideoStatus CameraStatus::getStatus() {
    return this->video_status;
}

void CameraStatus::setIsCameraRunning(bool running_state) {
    this->is_camera_running = running_state;
}

bool CameraStatus::getIsCameraRunning() {
    return this->is_camera_running;
}

void CameraStatus::setCameraStartTime() {
    this->start_time = ros::Time::now();
}

void CameraStatus::calculateActiveTime() {
    ros::Time current_time = ros::Time::now();
    this->duration_time = current_time - this->start_time;
    // ROS_INFO("duration: %lf", duration_time.toSec());
}

double CameraStatus::getDurationTime() {
    return this->duration_time.toSec();
}