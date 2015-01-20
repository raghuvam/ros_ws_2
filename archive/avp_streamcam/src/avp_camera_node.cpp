#include <ros/ros.h>
#include <nodelet/loader.h>

#include "tda2Cameras.h"


using namespace std;


int main(int argc, char **argv)
{
  ros::init(argc, argv, "avp_cam");
  cout <<"Node initated...constructor starting" <<endl;

  Tda2Cam avpCam(ros::NodeHandle(), ros::NodeHandle("~"));

  cout <<"Ok till here" <<endl;

  ros::spin();

  return 0;
}

