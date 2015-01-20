/*
 * dispCannedImgSeqMain.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: a0132147
 */
//============================================================================
// Name        : DispCannedImgSeqMain.cpp
// Author      : Udayan Dasgupta
// Version     : 0.1
// Copyright   : See AMUSE copyright
// Description : Example program for displaying MJPEG images
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "stdint.h"
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Display.h"

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <avp_streamcam/IPNC_client.h>
#include <fstream>
#include <string>

#include <sensor_msgs/fill_image.h>
#include <camera_info_manager/camera_info_manager.h>




using namespace cv;
using namespace std;
using namespace avp;

#if 0
int main(int argc, char *argv[])
{

	int maxNumCams = 1;
	int camNum;
	camNum = maxNumCams+1;
	//Linux location
	//PC location
	string fileStr_pre = ("/home/udayan/Downloads/test");
	string dispTitle_pre = ("Output from Camera # ");
	string fileStr_post = (".m4e");
	int start_x = 50, start_y = 20, incr_x = 150,incr_y = 0;
	float startFrFrac = -1, endFrFrac = -2;

	string camPath[maxNumCams+1];
	int vWidth[maxNumCams+1], vHeight[maxNumCams+1];
#if 0
	camPath[0] = ("rtsp://172.24.152.202:8555/PSIA/Streaming/channels/0?videoCodecType=MJPEG");
	vWidth[0] = 1920;
	vHeight[0] = 1080;
	camPath[1] = ("rtsp://172.24.152.202:8556/PSIA/Streaming/channels/2?videoCodecType=H.264");
	vWidth[1] = 720;
	vHeight[1] = 480;
#endif
	string fileLocation = "mem";
	string library;



	while (camNum > maxNumCams)
	{
		cout << "Which camera output do you want to see? (0 to " << maxNumCams << "). " << endl;
		cout <<		"To display all images input a negative number. " << endl;
	    cin >> camNum;
	    if (camNum > maxNumCams)
	    	cout << "Invalid Cam number ... input integer <= " << maxNumCams << ". " << endl;
	}


	if (fileLocation == "mem")
	{
		while (endFrFrac < startFrFrac)
		{
		  while ((startFrFrac < 0) || (startFrFrac > 1))
		  {
			  cout << "      Note that frameNum_fraction is calculated as (frameNum/totFrames)" << endl;
			  cout << "Starting Frame fraction do you want to see? (0 to 1)" << endl;
			  cin >> startFrFrac;
			  if ((startFrFrac < 0) || startFrFrac > 1)
				  cout << "Invalid Starting Frame fraction - Input fraction between 0 and 1 "  << endl;
		  }
		  while ((endFrFrac < 0) || (endFrFrac > 1))
		  {
			  cout << "      Note that frameNum_fraction is calculated as (frameNum/totFrames)" << endl;
			  cout << "Ending Frame fraction do you want to see? (0 to 1)" << endl;
			  cin >> endFrFrac;
			  if ((endFrFrac < 0) || endFrFrac > 1)
				  cout << "Invalid Ending Frame fraction - Input fraction between 0 and 1 "  << endl;
		  }
		  if (endFrFrac < startFrFrac)
		  {
			  cout << "Ending fraction needs larger than or equal to starting fraction  "  << endl;
			  // Reset  startFrFrac and startFrFrac
			  startFrFrac = -1;
			  endFrFrac = -2;
		  }
		}

		if (camNum < 0)
		{
			 Display myVideo(fileStr_pre,fileStr_post,dispTitle_pre, 0,maxNumCams+1,2,startFrFrac,endFrFrac,start_x,start_y,incr_x,incr_y);
			 cout << "Displaying all cam images ... " << endl;
			 myVideo.play_mem();
		}

		else
		{
		     Display myVideo(fileStr_pre,fileStr_post,dispTitle_pre, camNum,1,2,startFrFrac,endFrFrac,start_x,start_y,0,incr_y);
		     myVideo.play_mem();
		}
	}
	return 0;

}
#endif

typedef struct
{
  int width;
  int height;
  int bytes_per_pixel;
  int image_size;
  char *image;
  int is_new;
} tda2_cam_camera_image_t;

// start camera
tda2_cam_camera_image_t *tda2_cam_camera_start(const char* dev, int image_width, int image_height, int framerate);
// shutdown camera
void tda2_cam_camera_shutdown(void);
// grabs a new image from the camera
void tda2_cam_camera_grab_image(tda2_cam_camera_image_t *image);

static char *camera_dev;

tda2_cam_camera_image_t *tda2_cam_camera_start(const char* dev, int image_width, int image_height,
                                             int framerate)
{
  camera_dev = (char*)calloc(1, strlen(dev) + 1);
  strcpy(camera_dev, dev);

  tda2_cam_camera_image_t *image;
#if 0
  open_device();
  init_device(image_width, image_height, framerate);
  start_capturing();
#endif

  image = (tda2_cam_camera_image_t *)calloc(1, sizeof(tda2_cam_camera_image_t));

  image->width = image_width;
  image->height = image_height;
  image->bytes_per_pixel = 24;

  image->image_size = image->width * image->height * image->bytes_per_pixel;
  image->is_new = 0;
  image->image = (char *)calloc(image->image_size, sizeof(char));
  memset(image->image, 0, image->image_size * sizeof(char));

  return image;
}

void tda2_cam_camera_shutdown(void)
{
//  stop_capturing();
//  uninit_device();
//  close_device();

//  if (avcodec_context)
//  {
//    avcodec_close(avcodec_context);
//    av_free(avcodec_context);
//    avcodec_context = NULL;
//  }
//  if (avframe_camera)
//    av_free(avframe_camera);
//  avframe_camera = NULL;
//  if (avframe_rgb)
//    av_free(avframe_rgb);
//  avframe_rgb = NULL;
}

void tda2_cam_camera_grab_image(tda2_cam_camera_image_t *image)
{
#if 0
  fd_set fds;
  struct timeval tv;
  int r;

  FD_ZERO(&fds);
  FD_SET(fd, &fds);

  /* Timeout. */
  tv.tv_sec = 5;
  tv.tv_usec = 0;

  r = select(fd + 1, &fds, NULL, NULL, &tv);

  if (-1 == r)
  {
    if (EINTR == errno)
      return;

    errno_exit("select");
  }

  if (0 == r)
  {
    ROS_ERROR("select timeout\n");
    exit(EXIT_FAILURE);
  }


  read_frame(image);
#endif
  image->is_new = 1;
}


class Tda2CamNode
{
public:
  ros::NodeHandle node_;
  sensor_msgs::Image img_0_;
  sensor_msgs::Image img_1_;

  std::string video_file_name0_;
  std::string video_file_name1_;
//  std::string io_method_name_;
  int image_width_, image_height_, framerate_;
//  std::string pixel_format_name_;
//  bool autofocus_;

  std::string camera_name_0_;
  std::string camera_0_info_url_;

  std::string camera_name_1_;
  std::string camera_1_info_url_;

  ros::Time next_time_;
  int count_;

  tda2_cam_camera_image_t* camera_image_0_;
  tda2_cam_camera_image_t* camera_image_1_;

  image_transport::CameraPublisher image_pub_0_;
  image_transport::CameraPublisher image_pub_1_;

  boost::shared_ptr<camera_info_manager::CameraInfoManager> cinfo_0_;
  boost::shared_ptr<camera_info_manager::CameraInfoManager> cinfo_1_;

  Tda2CamNode() :
      node_("~")
  {
    image_transport::ImageTransport it_0(node_);
    image_transport::ImageTransport it_1(node_);
    image_pub_0_ = it_0.advertiseCamera("image_raw_0", 1);
    image_pub_1_ = it_1.advertiseCamera("image_raw_1", 1);

    node_.param("video_file_0", video_file_name0_, std::string("test.m4e"));
    node_.param("video_file_1", video_file_name1_, std::string("test.m4e"));
    node_.param("image_width", image_width_, 640);
    node_.param("image_height", image_height_, 480);
    node_.param("framerate", framerate_, 30);

    node_.param("camera_frame_id_0", img_0_.header.frame_id, std::string("avp_camera_0"));
    node_.param("camera_frame_id_1", img_1_.header.frame_id, std::string("avp_camera_1"));

    node_.param("camera_name_0", camera_name_0_, std::string("avp_camera_0"));
    node_.param("camera_name_1", camera_name_1_, std::string("avp_camera_1"));

    node_.param("camera_0_info_url", camera_0_info_url_, std::string(""));
    node_.param("camera_1_info_url", camera_1_info_url_, std::string(""));

    cinfo_0_.reset(new camera_info_manager::CameraInfoManager(node_, camera_name_0_, camera_0_info_url_));
    cinfo_1_.reset(new camera_info_manager::CameraInfoManager(node_, camera_name_1_, camera_1_info_url_));


    ROS_INFO("Camera name 0: %s", camera_name_0_.c_str());
    ROS_INFO("Camera name 1: %s", camera_name_1_.c_str());

    ROS_INFO("Camera 0 info url: %s", camera_0_info_url_.c_str());
    ROS_INFO("Camera 1 info url: %s", camera_1_info_url_.c_str());

    ROS_INFO("tda2_cam video_device 0 set to [%s]\n", video_file_name0_.c_str());
    ROS_INFO("tda2_cam video_device 1 set to [%s]\n", video_file_name1_.c_str());

    ROS_INFO("tda2_cam image_width set to [%d]\n", image_width_);
    ROS_INFO("tda2_cam image_height set to [%d]\n", image_height_);

    camera_image_0_ = tda2_cam_camera_start(video_file_name0_.c_str(), image_width_,
                                         image_height_, framerate_);

    camera_image_1_ = tda2_cam_camera_start(video_file_name1_.c_str(), image_width_,
                                         image_height_, framerate_);


    next_time_ = ros::Time::now();
    count_ = 0;
  }

  virtual ~Tda2CamNode()
  {

    tda2_cam_camera_shutdown();
  }

  bool take_and_send_image(tda2_cam_camera_image_t* camera_image,sensor_msgs::Image img,boost::shared_ptr<camera_info_manager::CameraInfoManager> cinfo, image_transport::CameraPublisher image_pub)
  {
    tda2_cam_camera_grab_image(camera_image);

    fillImage(img, "rgb8", camera_image->height, camera_image->width, 3 * camera_image->width,camera_image->image);
    img.header.stamp = ros::Time::now();

    sensor_msgs::CameraInfoPtr ci(new sensor_msgs::CameraInfo(cinfo->getCameraInfo()));
    ci->header.frame_id = img.header.frame_id;
    ci->header.stamp = img.header.stamp;
    image_pub.publish(img, *ci);


    return true;
  }

  bool spin()
  {
    while (node_.ok())
    {
      if (take_and_send_image(camera_image_0_,img_0_,cinfo_0_,image_pub_0_) && take_and_send_image(camera_image_1_,img_1_,cinfo_1_,image_pub_1_))
      {
        count_++;
        ros::Time now_time = ros::Time::now();
        if (now_time > next_time_)
        {
          ROS_DEBUG("%d frames/sec", count_);
          count_ = 0;
          next_time_ = next_time_ + ros::Duration(1, 0);
        }
      }
      else
      {
        ROS_ERROR("couldn't take image.");
        usleep(1000000);
      }
//      self_test_.checkTest();
    }
    return true;
  }
};

class StereoCamera {
  public:
    StereoCamera(ros::NodeHandle comm_nh, ros::NodeHandle param_nh);
    void onInit();
    void sendInfo(ros::Time time);
    void feedImages();
    ~StereoCamera();

  private:
    ros::NodeHandle node, pnode;
    image_transport::ImageTransport it;
    bool ok;

    uvc_cam::Cam *cam_left, *cam_right;
    int width, height, fps, skip_frames, frames_to_skip;
    std::string left_device, right_device, frame;
    bool rotate_left, rotate_right;

    camera_info_manager::CameraInfoManager left_info_mgr, right_info_mgr;

    image_transport::Publisher left_pub, right_pub;
    ros::Publisher left_info_pub, right_info_pub;

    boost::thread image_thread;
};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "avp_cam");
  cout <<"Node initated...constructor starting" <<endl;
//  Tda2CamNode avpCam;

//  avpCam.spin();


//  ros::init(argc, argv, "uvc_camera_stereo");

  Tda2CamNode avpCam(ros::NodeHandle(), ros::NodeHandle("~"));
  cout <<"Ok till here" <<endl;

  ros::spin();

  return 0;
}





