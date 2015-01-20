/*
 * vlc.h
 *
 *  Created on: Mar 3, 2014
 *      Author: a0132147
 */

#ifndef VLC_H_
#define VLC_H_

#include <iostream>
#include <string>
#include <vlc/vlc.h>
#include <opencv2/highgui/highgui.hpp>

typedef unsigned char uchar;

namespace vlc {

class vlcClass {
public:
   vlcClass(const std::string camPath[], const int *vWidth, const int *vHeight, const std::string dispStr_pre,const int firstCamNum, const int numCam,const int dispStart_x,const int dispStart_y,const int dispIncr_x,const int dispIncr_y);
   virtual ~vlcClass();
   void play();
private:
   static void display(void *data, void *id);
   static void unlock(void *data, void *id, void *const *p_pixels);
   static void *lock(void *data, void **p_pixels);
   libvlc_instance_t *libvlc;
   libvlc_media_t *media;
   libvlc_media_player_t *mediaPlayer;
	std::string dispTitle_pre; //!< First (common) part of display window title
	std::string dispTitle; //!< Complete display window title
	int firstCamNum; //!< First camera video/image sequence to be display
	int numCam; //!< Number of Cameras to be displayed
	int dispStart_x; //!< X-coord of first display window
	int dispStart_y; //!< Y-coord of first display window
	int dispIncr_x; //!< Increment in X-coord of display windows
	int dispIncr_y; //!< Increment in Y-coord of display windows
	const std::string *camPath;
	const int *vWidth;
	const int *vHeight;
};

}

#endif /* VLC_H_ */
