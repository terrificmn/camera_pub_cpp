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

    CameraDriver* camObj = nullptr;
    camObj = new CameraDriver;
    CameraStatus camStatusObj;

    ros::Rate loop_rate(rate);
    while (ros::ok()) {
        // to do: 두번씩 들어오거나 못하게 업데이트, 현재 status는 구독이후(cb function에서) 바로 변경되므로 참고
        if(camStatusObj.getStatus() == VideoStatus::NORMAL_START) { // default
            // camObj.input_video.set(cv2.CV_CAP_PROP_FPS, rate);
            camObj->input_video.open(camera_dev_id);
            if(!camObj->input_video.isOpened()) {
                ROS_ERROR("Failed to open the camera. Please make sure that a camera is connected");
                return 1;
            }
            camStatusObj.setStatus(VideoStatus::ACTIVE);

        } else if(camStatusObj.getStatus() == VideoStatus::RESTART) {
            if(!camObj) {
                // delete 후  nullptr로 만들어짐
                ROS_WARN("camera will be resumed");
                
                // to do delete가 확실히 되는지 테스트 필요
                camObj->test(); // 되었어도 아마도 delete가 잘 안된 듯 하다. 기능이 작동한다;;;
                camObj = new CameraDriver; // delete 된 후에 다시 할당

                camObj->input_video.open(camera_dev_id);
                if(!camObj->input_video.isOpened()) {
                    ROS_ERROR("Failed to open the camera. Please make sure that a camera is connected");
                    return 1;
                }
                camStatusObj.setStatus(VideoStatus::ACTIVE);

            } else {
                ROS_ERROR("IT's not null. This should be nullptr. Program is terminated");
                return 1;
            }
        }

        // only do when active
        if(camStatusObj.getStatus() == VideoStatus::ACTIVE) {
            camObj->input_video.read(camObj->frame);
            camObj->camPublish();

            // disabled by param
            if(enable_imgshow) {
                imshow("img_out.jpg", camObj->frame);
                if(cv::waitKey(1) > 0);
            }
        }
        
        if(camStatusObj.getStatus() == VideoStatus::REQUEST_STOP) {
            ROS_WARN("camera will be stopped");
            camStatusObj.setStatus(VideoStatus::STOPPED); //status update
            delete camObj;
            camObj = nullptr;
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::shutdown();
    return 0;
}
