#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <avp_streamcam/IPNC_client.h>
#include <fstream>
#include <string>

#define WIDTH 1920
#define HEIGHT 1080

std::string IP_ADDR;
int PORT_NO;

image_transport::Publisher RAWpub;

void RAWpublish(char *in_image)
{
        cv::Mat bayer16Bit(HEIGHT,WIDTH,CV_16UC1,in_image);
        cv::Mat bayer8Bit;
        bayer16Bit.convertTo(bayer8Bit, CV_8UC1, 0.0625);
	
	cv_bridge::CvImage out_image;
	out_image.encoding = sensor_msgs::image_encodings::BAYER_GRBG8;
	out_image.image = bayer8Bit;

	RAWpub.publish(out_image.toImageMsg());
        ROS_INFO_STREAM("Published RAW image");
}
#if 0

void triggerReceived(const std_msgs::Bool& msg) {
	ROS_INFO_STREAM("Received command to capture raw image");

	char *in_image;
	in_image = new char[WIDTH*HEIGHT*2];

//	std::ifstream myfile;
//	myfile.open ("~/ros/src/avp_cam/example_2504.raw");
//	myfile.read(in_image, WIDTH*HEIGHT*2);
	if (IPNC::capture(IP_ADDR.c_str(), PORT_NO, in_image) != 0)
    		ROS_INFO_STREAM("Returned from IPNC_client with errors");

	IPNC::closeIPNC();

	RAWpublish(in_image);

	delete[] in_image;
}

#endif 
int main (int argc, char **argv) {
	ros::init(argc, argv, "capture");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);

#if 0
	bool ok1 = ros::param::get("~ip_address", IP_ADDR);
        bool ok2 = ros::param::get("~port_no", PORT_NO);
	if(!ok1 or !ok2) {
		ROS_FATAL_STREAM("Could not get parameters");
		exit(1);
	}
#endif
        std::string IP_ADDR ="10.0.2.15";
	int PORT_NO = 8554;

	ROS_INFO_STREAM("ip_address = " << IP_ADDR << " port_no = " << PORT_NO);

#if 1 //test this out
	char *in_image;
	in_image = new char[WIDTH*HEIGHT*2];

//	std::ifstream myfile;
//	myfile.open ("~/ros/src/avp_cam/example_2504.raw");
//	myfile.read(in_image, WIDTH*HEIGHT*2);
	ROS_INFO_STREAM("1");
	if (IPNC::capture(IP_ADDR.c_str(), PORT_NO, in_image) != 0)
    		ROS_INFO_STREAM("Returned from IPNC_client with errors");
	ROS_INFO_STREAM("2");
	IPNC::closeIPNC();
	ROS_INFO_STREAM("3");
	RAWpublish(in_image);
	ROS_INFO_STREAM("4");
	delete[] in_image;

#endif

//        ros::Subscriber sub = nh.subscribe("avp_streamcam/trigger_cmd", 1000, &triggerReceived);
//	RAWpub = it.advertise("avp_streamcam/image_raw", 1000);

//	ros::spin();
}
