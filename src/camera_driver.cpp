#include <camera_driver.h>

CameraDriver::CameraDriver() {
    ROS_INFO("Camera Init");

    ptrIt = new image_transport::ImageTransport(nh);
    this->img_pub = ptrIt->advertise(this->cam_topic, 1);
}

CameraDriver::~CameraDriver() {
    delete ptrIt;
    ROS_INFO("Deleted and Destructed");
}

void CameraDriver::camPublish() {
    //msg 
    this->cvi_msg.header.frame_id = "image";
    this->cvi_msg.encoding = sensor_msgs::image_encodings::BGR8;
    this->cvi_msg.image = this->frame;
    this->cvi_msg.header.stamp = ros::Time::now();

    this->img_pub.publish(this->cvi_msg.toImageMsg());
}


// test
void CameraDriver::test(){
    ROS_INFO("***test");

}