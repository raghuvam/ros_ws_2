// Include the ROS C++ APIs
#include <ros/ros.h>
#include <ros/time.h>
#include <nodelet/loader.h>
#include "sensor_msgs/Image.h"
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/image_encodings.h"
#include "sensor_msgs/CameraInfo.h"
#include "camera_info_manager/camera_info_manager.h"
#include "image_transport/image_transport.h"
#include "image_transport/simple_publisher_plugin.h"
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
using namespace cv;
using namespace sensor_msgs;

// parameters for image transport
int i=0;
char filename[30]="images/test";
FILE *stream;
unsigned int pair_id = 0;
image_transport::Publisher cam_pub_0_;
image_transport::Publisher cam_pub_1_;
int length;

//cannyedge detection variables
int lowThreshold = 35;
int ratio = 3;
int kernel_size =3;

cv::Mat cannyEdgeDetector(cv::Mat& imgEnc)
{
  cv::Mat imgEdges;
  cv::Mat imgGrey;
  cv::Mat imgResized;
  cv::Mat imgDec= cv::imdecode(imgEnc, CV_LOAD_IMAGE_COLOR);
  
 cv::resize(imgDec,imgDec,cv::Size(640,360));
  cv::cvtColor( imgDec, imgGrey, CV_RGB2GRAY );
  cv::blur( imgGrey, imgEdges, Size(3,3));
  cv::Canny( imgEdges, imgEdges, lowThreshold, lowThreshold*ratio, kernel_size);
  return imgEdges;
}

extern "C"
{
#include "main.h"

int frameStreamHandler(void *bufAddr,int fillLength,FILE *fpDataStream,int width,int height)
{


	cv::Mat imageNew(1,fillLength,CV_8U);
	
	length = (int)fillLength;

	printf("fillLength: %d addr: %x",fillLength,bufAddr);

	memcpy(imageNew.data,bufAddr,length);

	ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::MONO8, imageNew).toImageMsg();

	ROS_INFO_STREAM("debug: image published");
	
	cam_pub_0_.publish(msg);

  //Publish canny images
	//ImagePtr canny_msg = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::MONO8, cannyEdgeDetector(imageNew)).toImageMsg();
  	//cam_pub_1_.publish(canny_msg);

return 0;
}

}

int main(int argc, char** argv) 
{

  ros::init(argc, argv, "cam_streamer");
 
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh); 
  cam_pub_0_ = it.advertise("image/compressed", 1);
  cam_pub_1_ = it.advertise("image/cannyEdges",1);
  ros::start();

  ROS_INFO_STREAM("Hello, This is cam_streamer");


  /////////// VISION_SDK_CODE ////////////

  VisionSDK_main();

  ////////////////////////////////////////

  ros::spin();
  ros::shutdown();

  return 0;
}
