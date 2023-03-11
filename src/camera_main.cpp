#include <ros/ros.h>
#include <camera_driver.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "camera_publish_node");
    ros::NodeHandle nh;

    // prameters set
    int camera_dev_id = -1, rate = 30; //default
    bool enable_imgshow = false;
    int timeout = 5;
    nh.getParam( "camera_id", camera_dev_id);
    nh.getParam( "rate", rate);
    nh.getParam( "enable_imgshow", enable_imgshow);
    nh.getParam( "timeout", timeout);
    int timeout_sec = timeout * 60;
    ROS_INFO("timeout_sec: %d", timeout_sec);

    if(camera_dev_id == -1) {
        ROS_WARN("Please check camera id. You may try to type below..");
        ROS_WARN("ls -l /dev/video*");
        ROS_WARN("camera_publish_node is terminated..");
        return 1;
    }

    CameraDriver* camObj = nullptr;
    CameraStatus camStatusObj;

    ros::Rate loop_rate(rate);
    while (ros::ok()) {
        if(camStatusObj.getStatus() == VideoStatus::INACTIVE ||
            (camStatusObj.getStatus() == VideoStatus::CAMERA_START && camStatusObj.getIsCameraRunning() == false)) { // default or request to start
            // camObj.input_video.set(cv2.CV_CAP_PROP_FPS, rate);
            ROS_WARN("camera is turned on");
            camStatusObj.setIsCameraRunning(true);
            camObj = new CameraDriver;  // 처음 시작하거나, delete 후 다시 할당
            camObj->input_video.open(camera_dev_id);
            if(!camObj->input_video.isOpened()) {
                ROS_ERROR("Failed to open the camera. Please make sure that a camera is connected");
                return 1;
            }
            camStatusObj.setStatus(VideoStatus::ACTIVE);
            camStatusObj.setCameraStartTime();

        } else if(camStatusObj.getStatus() == VideoStatus::ACTIVE) {              // only do when active
            camObj->input_video.read(camObj->frame);
            camObj->camPublish();

            // calculate active time
            camStatusObj.calculateActiveTime();
            if(camStatusObj.getDurationTime() > timeout_sec) {
                //force to change the camera's status
                camStatusObj.setStatus(VideoStatus::REQUEST_STOP);
            }

            // disabled by param
            if(enable_imgshow) {
                imshow("img_out.jpg", camObj->frame);
                if(cv::waitKey(1) > 0);
            }
        }
        
        if(camStatusObj.getStatus() == VideoStatus::REQUEST_STOP) {
            ROS_WARN("camera will be stopped");
            camStatusObj.setStatus(VideoStatus::STOPPED); //status update
            camStatusObj.setIsCameraRunning(false);
            delete camObj;
            camObj = nullptr;
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::shutdown();
    return 0;
}
