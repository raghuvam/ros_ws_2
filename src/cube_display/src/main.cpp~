
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int m = 0;
int height =720;
int width =1280;

extern "C"
{
#include "common.h"
#include <stdio.h>
//#include <file.h>
#include <string.h>
#define SAT(c) \
   if (c & (~255)) { if (c < 0) c = 0; else c = 255; }


void getImage(unsigned char*src,unsigned char *dst)
{





/*
for (h=0; h<720; h++)
	for(w=0;w<1280*4;w++)
		dst[h*1280*4 + w] = src[h*1280*4 + w];
*/




/*
memcpy(dst,src,fillLength);

cout << "copying to Mat image  " << endl ;
Mat image(height,width,CV_8UC4,src);
vector<Mat> channels(4);
split(image, channels);
Mat img3;
merge(channels[1],channels[2],channels[4],img3);

cout << "size: " << img3.size() << endl;
cvtColor(image, image,CV_YCrCb2RGB,3);

static void
yuyv_to_rgb24 (int width, int height, unsigned char *src, unsigned char *dst)
{
*/

cout << "debug 1" << endl;
///////
   unsigned char *s;
   unsigned char *d;
   int l, c;
   int r, g, b, cr, cg, cb, y1, y2;

   l = height;
   s = src;
   d = dst;
   while (l--) {
      c = width >> 1;
      while (c--) {
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

     *d++ = b;
     *d++ = g;
     *d++ = r;

         r = y2 + cr;
         b = y2 + cb;
         g = y2 - cg;
         SAT(r);
         SAT(g);
         SAT(b);

     *d++ = b;
     *d++ = g;
     *d++ = r;
      }
   }
/////////

cout << "debug 2" << endl;
m++;
FILE *stream;

int fillLength = height*width*2;

char prefix[50] = "./images/";

char filename[50];

cout << "debug 3" << endl;
sprintf(filename, "img_%d.jpg", m);

cout << "debug 4" << endl;
strcat(prefix,filename);

stream = fopen(prefix,"w");

fwrite(src,fillLength,1,stream);

fclose(stream);
fflush(stream);



/*

Mat imdst(1,height*width*3,CV_8UC1);
cout << "memcpy 1" << endl;

memcpy(imdst.data,dst,height*width*3);

cout << "debug 2" << endl;
Mat imdec = imdecode(imdst,1);
cout << "debug 5" << endl;


imwrite(prefix,imdec);
*/

/*

*/

/*
int fillLength = 2*height*width;

cout << "fillLength: " << fillLength << endl;
char filename[20] = "image1";

cv::Mat imgrgb(1,fillLength,CV_16UC1);

cout << "debug: 1" << endl;
memcpy(imgrgb.data,dst,fillLength);

cout << "debug: 2" << endl;
cv::Mat imdec = imdecode(imgrgb,CV_LOAD_IMAGE_COLOR);

cout << "debug: 3" << endl;
cv::imwrite(filename,imdec);
*/



}

}

int main (int argc, char** argv)
{
cout << "calling buf main" << endl ;

bufDisplay_main(argc,argv);

return 0;
}

