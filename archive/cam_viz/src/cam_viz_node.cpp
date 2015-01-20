

#include <ros/ros.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;

cv::Mat frame;
cv::VideoWriter rec;

int main(int argc, char** argv)
{

ros::init(argc,argv,"stream_display");

VideoCapture cap(1);

if(!cap.isOpened())
{
ROS_INFO("Couldn't open the camera");
}

namedWindow("video",CV_WINDOW_AUTOSIZE);

while(ros::ok())
{
bool captured = cap.read(frame);

if(!captured)
{
ROS_INFO("Couldn't capture the image");
}

imshow("video", frame);

waitKey(30);

}


return 0;
}

