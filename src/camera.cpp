#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "cv_bridge/cv_bridge.h"
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>


class CameraDriver {
private:
    int id_camera;
    int fps;
    bool show;
    cv::VideoCapture input_video;
    cv::Mat frame;
    
    cv_bridge::CvImage cvi;
    image_transport::ImageTransport *it;
    image_transport::Publisher pub;

public:
    CameraDriver() {
        ROS_INFO("Camera Init");
        ros::NodeHandle nh("~");
        nh.param( "camera_index", id_camera, -1);
        nh.param( "show", show , false );
        nh.param( "fps", fps , 30 );

        cvi.header.frame_id = "image";
        cvi.encoding = sensor_msgs::image_encodings::BGR8;

        it = new image_transport::ImageTransport(nh);

        std::string cam_topic = "/camera/color/image_raw";
        pub = it->advertise(cam_topic, 1);

        if(id_camera == -1) {
            ROS_WARN("camera's id has not recived");
            ROS_WARN("Every camera would be opened that is found");
            ROS_WARN("Now start to advertise %s", cam_topic.c_str());
        }

        input_video.open(id_camera);

        // input_video.set(cv2.CV_CAP_PROP_FPS, fps);

        if(!input_video.isOpened()) {
            ROS_ERROR("Couldn't Open The Camera !");
            ROS_ERROR("Make sure that a cam is connected to a computer.");
            ros::shutdown();
        }

        ros::Rate loop_rate(fps);

        while (ros::ok()) {
            input_video.read(frame);
            cvi.image=frame;
            cvi.header.stamp = ros::Time::now();
            pub.publish(cvi.toImageMsg());

            if(show) {
                imshow("imgout.jpg", frame);
                if(cv::waitKey(1) > 0);
            }

        loop_rate.sleep();
    }
    }

};

int main(int argc, char** argv) {
    ros::init(argc, argv, "publish_camera_image_raw");

    CameraDriver camObj;

    ros::shutdown();
    return 0;
}