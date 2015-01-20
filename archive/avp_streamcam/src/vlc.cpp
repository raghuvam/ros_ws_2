/*
 * vlc.cpp
 *
 *  Created on: Mar 3, 2014
 *      Author: a0132147
 */
#include "vlc.h"
#include <string>

using namespace std;

struct ctx
{
    IplImage* image;
//    HANDLE mutex;
    uchar*    pixels;
};

namespace vlc {

	void *vlcClass::lock(void *data, void**p_pixels)
	{
		struct ctx *ctx = (struct ctx*)data;
	//    WaitForSingleObject(ctx->mutex, INFINITE);
		*p_pixels = ctx->pixels;
		return NULL;

	}
	void vlcClass::display(void *data, void *id)
	{
		(void) data;
		assert(id == NULL);
	}

	void vlcClass::unlock(void *data, void *id, void *const *p_pixels){
		struct ctx *ctx = (struct ctx*)data;
		// VLC just rendered the video, but we can also render stuff
		uchar *pixels = (uchar*)*p_pixels;
		cvShowImage("image", ctx->image);
	 //   ReleaseMutex(ctx->mutex);
		assert(id == NULL); // picture identifier, not needed here
	}

	vlcClass::vlcClass(const string *camPath_b,const int *vWidth_b,const int *vHeight_b,const string dispStr_pre_b,const int firstCamNum_b, const int numCam_b,const int dispStart_x_b,const int dispStart_y_b,const int dispIncr_x_b,const int dispIncr_y_b) {
	   // TODO Auto-generated constructor stub
	    camPath = camPath_b;
	    vWidth = vWidth_b;
	    vHeight = vHeight_b;
	    dispTitle_pre = dispStr_pre_b;
        firstCamNum = firstCamNum_b;
        numCam = numCam_b;
        dispStart_x = dispStart_x_b;
        dispStart_y = dispStart_y_b;
        dispIncr_x = dispIncr_x_b;
        dispIncr_y = dispIncr_y_b;
	}

	void vlcClass::play() {
		cout << "here" <<endl;
        ostringstream convert2Str;
        convert2Str << firstCamNum;
	    dispTitle = dispTitle_pre + convert2Str.str();

	   cvNamedWindow("image", CV_WINDOW_AUTOSIZE);

	   char const *vlc_argv[] =
	   {
		  "-vvv",
		  "--network-caching=100", // libvlc is keeping a buffer and that is why we see a latency
	   };

	   int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
	   libvlc = libvlc_new(vlc_argc, vlc_argv);
	   media = libvlc_media_new_location(libvlc, camPath[firstCamNum].c_str());
	   mediaPlayer = libvlc_media_player_new_from_media(media);
	   libvlc_media_release(media);

	   struct ctx* context = ( struct ctx* )malloc( sizeof( *context ) );
	 //  context->mutex = CreateMutex(NULL, FALSE,NULL);
	   context->image = cvCreateImage(cvSize(vWidth[firstCamNum],vHeight[firstCamNum]), IPL_DEPTH_8U, 4);
	   context->pixels = (unsigned char *)context->image->imageData;

	   libvlc_video_set_callbacks(mediaPlayer, lock, unlock, display, context);
	   libvlc_video_set_format(mediaPlayer, "RV32", vWidth[firstCamNum], vHeight[firstCamNum], vWidth[firstCamNum]*4);
	   libvlc_media_player_play(mediaPlayer);

	}

	vlcClass::~vlcClass() {
	   // TODO Auto-generated destructor stub

		/* Stop playing */
		libvlc_media_player_stop (mediaPlayer);

		/* Free the media_player */
		libvlc_media_player_release (mediaPlayer);

		libvlc_release (libvlc);
	}
}



