
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int height =720;
int width =1280;

extern "C"
{
  #include "common.h"
  #include <stdio.h>
  #include <string.h>

  // fun() to confine the pixel value btwn 0-255
  #define SAT(c) \
  if (c & (~255)) { if (c < 0) c = 0; else c = 255; }


  //Returns the image with canny edges
  cv::Mat cannyEdgeDetector(cv::Mat& imgEnc)
{
  //canny edge detection parameters
  int lowThreshold =35;
  int ratio = 3;
  int kernel_size =3;

    cv::Mat imgEdges,imgGrey,imgResized;

    // convert RGB Mat image to Gray Mat.
    cv::cvtColor( imgEnc, imgGrey, CV_RGB2GRAY );

    // Apply guassian blur to remove noise
    cv::blur( imgGrey, imgEdges, Size(3,3));

    // Apply canny edge detection
    cv::Canny( imgEdges, imgEdges, lowThreshold, lowThreshold*ratio, kernel_size);

    //return gray image with edges detected
    return imgEdges;
}

//This function converts gray Mat image to yuyu image i.e  unsigned char *dst.
void gray2yuv(Mat &imgray,unsigned char *dst)
{

  int i, j;
  for (j = 0; j < 720; j++) {

    //derefence the pointer ptr to the first element of the row in dst pointer
    uint8_t *ptr = (uint8_t*)((char*)dst + j * 1280*2);

    for (i = 0; i < 1280; i++) {

      //Converting gray to YU-YV pixel
      *(ptr++) = imgray.at<uchar>(j,i);
      *(ptr++) = 128;
    }
  }



}

//This function converts rgb Mat image to yuyu image i.e  unsigned char *dst.
void rgb2yuv(Mat &imgray,unsigned char *dst)
{

  int i, j;

  // resize the image
  resize(imgray,imgray,cv::Size(640,720));

  int red, green, blue;

  for (j = 0; j < 720; j++) {

    //derefence the pointer ptr to the first element of the row in dst pointer
    uint8_t *ptr = (uint8_t*)((char*)dst + j * 1280*2);

    for (i = 0; i < 1280; i++) {

      // rgb valu access
        red   = imgray.at<cv::Vec3b>(j,i)[0];
        green = imgray.at<cv::Vec3b>(j,i)[1];
        blue  = imgray.at<cv::Vec3b>(j,i)[2];

      // Converting a rgb pixel to YU-YV (i.e two pixels)

      unsigned char y = (0.299 * red) + (0.587 * green) + (0.114 * blue);

      *(ptr++) = y;
      *(ptr++) = (blue - y) * 0.565 + 128;
      *(ptr++) = y;
      *(ptr++) = (red - y) * 0.713 + 128;
    }
  }



}

//convert yuyv pointer to RGB Mat image
cv::Mat yuyv2rgb(unsigned char *src)
{

  // RGB Mat image
  Mat imRGB(720,1280,CV_8UC3);

  uint8_t *s, *d;
  int l, c;
  int r, g, b, cr, cg, cb, y1, y2;
  int h=0;
  int w=0;
  l = height;

  s = src;

  // converting YU-YV to RGB-RGB pixel (creates rgb image of same size h,w)
  while (l--) {

    c = width >> 1;

    while (c--)
    {
      y1 = *s++;
      cb = ((*s - 128) * 454) >> 8;
      cg = (*s++ - 128) * 88;
      y2 = *s++;
      cr = ((*s - 128) * 359) >> 8;
      cg = (cg + (*s++ - 128) * 183) >> 8;

      r = y1 + cr;
      b = y1 + cb;
      g = y1 - cg;
      SAT(r);
      SAT(g);
      SAT(b);

      //aasigning r,g,b pixel values in RGB Mat image.
      imRGB.at<cv::Vec3b>(h,w)[0] = r;
      imRGB.at<cv::Vec3b>(h,w)[1] = g;
      imRGB.at<cv::Vec3b>(h,w)[2] = b;
      w++;

      r = y2 + cr;
      b = y2 + cb;
      g = y2 - cg;
      SAT(r);
      SAT(g);
      SAT(b);

      //aasigning r,g,b pixel values in RGB Mat image.
      imRGB.at<cv::Vec3b>(h,w)[0] = r;
      imRGB.at<cv::Vec3b>(h,w)[1] = g;
      imRGB.at<cv::Vec3b>(h,w)[2] = b;
      w++;
    }
    h++;
    w=0;
  }

  return imRGB;

}

void getImage(unsigned char*src,unsigned char *dst)
{

  // format to create a temp yuyv image
  //uint8_t *src = (uint8_t *)malloc(sizeof(uint8_t *)*height*width*2);

  // get rgb mat image from src
  cout << "yuyv -> rgb " << endl;
  Mat imRgb = yuyv2rgb(src);

  // get canny edge image
  cout << "rgb -> canny edges gray image " << endl;
  Mat imgray = cannyEdgeDetector(imRgb);

  // convert gray to yuyv image to display on kms cube
  cout << "gray -> yuyv" << endl;
  gray2yuv(imgray,dst);

}

}

int main (int argc, char** argv)
{
  cout << "calling buf main" << endl ;

  bufDisplay_main(argc,argv);

  return 0;
}
