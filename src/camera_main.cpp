#include <ros/ros.h>
#include <camera_driver.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "camera_publish_node");
    ros::NodeHandle nh;

    int camera_dev_id = -1, rate = 30; //default
    bool enable_imgshow = false;
    nh.getParam( "camera_id", camera_dev_id);
    nh.getParam( "rate", rate);
    nh.getParam( "enable_imgshow", enable_imgshow);

    if(camera_dev_id == -1) {
        ROS_WARN("Please check camera id. You may try to type below..");
        ROS_WARN("ls -l /dev/video*");
        ROS_WARN("camera_publish_node is terminated..");
        return 1;
    }

    CameraDriver camObj;
    camObj.input_video.open(camera_dev_id);
    if(!camObj.input_video.isOpened()) {
        ROS_ERROR("Failed to open the camera. Please make sure that a camera is connected");
        return 1;
    }

    ros::Rate loop_rate(rate);
    while (ros::ok()) {
        camObj.input_video.read(camObj.frame);
        camObj.camPublish();

        // disabled by a config file
        if(enable_imgshow) {
            imshow("img_out.jpg", camObj.frame);
            if(cv::waitKey(1) > 0);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::shutdown();
    return 0;
}
