#include <boost/thread.hpp>

#include <ros/ros.h>
#include <ros/time.h>

#include "sensor_msgs/Image.h"
#include "sensor_msgs/image_encodings.h"
#include "sensor_msgs/CameraInfo.h"
#include "camera_info_manager/camera_info_manager.h"
#include "image_transport/image_transport.h"


class Tda2Cam {
  public:
    Tda2Cam(ros::NodeHandle comm_nh, ros::NodeHandle param_nh);
    void onInit();
    void sendInfo(ros::Time time);
    void feedImages();
    ~Tda2Cam();

  private:
    ros::NodeHandle node_, pnode_;
    image_transport::ImageTransport it_;
    bool ok_;

    int width_, height_, fps_, skip_frames_, frames_to_skip_;

    std::string camSrc_0_, camSrc_1_, frame_;

    camera_info_manager::CameraInfoManager cam_info_mgr_0_, cam_info_mgr_1_;

    image_transport::Publisher cam_pub_0_, cam_pub_1_;
    ros::Publisher cam_info_pub_0_, cam_info_pub_1_;

    boost::thread image_thread;
};


