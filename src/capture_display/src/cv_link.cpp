

#include "cv_link.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

int height =720;
int width =1280;


extern "C" void getImage(int* cvBuf)
{

Mat image = imread("~/image",0);

int fillLength = height*width;

cout << "size: " << image.size() << endl;
memcpy(cvBuf,image.data,fillLength);



}

