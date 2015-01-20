


#include "ros/ros.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

extern "C"
{
#include "common.h"

void* getImageBuffer()
{

cv::Mat imtest = cv::imread("1.jpg",CV_LOAD_IMAGE_COLOR);

int size = imtest.rows*imtest.cols;

unsigned char* buffer = new unsigned char[size];

memcpy(buffer,imtest.data,size*sizeof(unsigned char));

return buffer;

} 
}

int main(int argc, char ** argv)
{
ros::init(argc,argv, "kmscube_node");
ros::NodeHandle nh;

ROS_INFO("This is KMSCUBE NODE");

cv:: Mat imTest = cv::imread("1.jpg",CV_LOAD_IMAGE_COLOR);

int imSize = imTest.rows*imTest.cols;

unsigned char* buf = (unsigned char*)getImageBuffer();

//////////
kmscube_main(buf,imSize);
/////////

return 0;
}
