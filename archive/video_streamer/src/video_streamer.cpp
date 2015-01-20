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
using namespace std;
// parameters for image transport
int i=0;
char filename[30]="images/test";
FILE *stream;
unsigned int pair_id = 0;
image_transport::Publisher cam_pub_0_;
image_transport::Publisher cam_pub_1_;
int length;

//cannyedge detection variables


extern "C"
{
#include "main.h"
cv::Mat cannyEdgeDetector(cv::Mat& imgEnc)
{
	int lowThreshold = 35;
int ratio = 3;
int kernel_size =3;


  cv::Mat imgEdges;
  cv::Mat imgGrey;
  cv::Mat imgResized;
 // cv::Mat imgDec= cv::imdecode(imgEnc, CV_LOAD_IMAGE_COLOR);
  
  cv::resize(imgEnc,imgEnc,cv::Size(640,360));
  cv::cvtColor( imgEnc, imgGrey, CV_BGR2GRAY );
  cv::blur( imgGrey, imgEdges, Size(3,3));
  cv::Canny( imgEdges, imgEdges, lowThreshold, lowThreshold*ratio, kernel_size);
  return imgEdges;
}


int frameStreamHandler()
{

	VideoCapture cap("./test.mp4");

	 if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the video file" << endl;
         return -1;
    }


while(1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

	if (!bSuccess) //if not success, break loop
	{
                        cout << "Cannot read the frame from video file" << endl;
			break;
	}

	
	ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::BGR8, frame).toImageMsg();

	//ROS_INFO_STREAM("debug: image published");
	
	cam_pub_0_.publish(msg);

	//Publish canny images
	ImagePtr canny_msg = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::MONO8, cannyEdgeDetector(frame)).toImageMsg();
	cam_pub_1_.publish(canny_msg);

       

        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
	{
                cout << "esc key is pressed by user" << endl;
		break; 
	}
    }

	
return 0;
}

}

int main(int argc, char** argv) 
{

  ros::init(argc, argv, "video_streamer");
 
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh); 
  cam_pub_0_ = it.advertise("image/compressed", 1);
  cam_pub_1_ = it.advertise("image/cannyEdges",1);
  ros::start();

  ROS_INFO_STREAM("Hello, This is video_streamer");


  /////////// VIDEO_STREAMER ////////////

  frameStreamHandler();

  ////////////////////////////////////////

  ros::spin();
  ros::shutdown();

  return 0;
}
