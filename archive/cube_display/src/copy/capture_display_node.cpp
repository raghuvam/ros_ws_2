


#include "ros/ros.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

extern "C"
{

#include "common.h"


}

int height =720;
int width =1280;


extern "C" void getImage(int* cvBuf)
{

Mat image = imread("~/image",0);

int fillLength = height*width;

cout << "size: " << image.size() << endl;
memcpy(cvBuf,image.data,fillLength);


}


int main(int argc, char ** argv)
{
ros::init(argc,argv, "kmscube_node");
ros::NodeHandle nh;

ROS_INFO("This is KMSCUBE NODE");

//////////
bufDisplay_main(argc,argv);
/////////


return 0;
}
