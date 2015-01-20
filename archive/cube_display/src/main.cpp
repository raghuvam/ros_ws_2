
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

void getImage(unsigned char* src,unsigned char* dst)
{


cout << "get image function" << endl; 

int fillLength = height*width*4;

memcpy(dst,src,sizeof(unsigned char*)*fillLength);

/*
Mat image = imread("~/image",CV_LOAD_IMAGE_COLOR);


cout << "Image is continuous " << endl ;


cout << "size: " << image.size() << endl;
cvtColor(image, image,CV_RGB2YCrCb,3);

*/


}

}

int main (int argc, char** argv)
{
cout << "calling buf main" << endl ;

bufDisplay_main(argc,argv);

return 0;
}

