/*
 * Display.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: a0132147
 */
/*! \file 	Display.cpp
 * 	\brief 	Contains Display class implementations
 *
 * 	\author Udayan Dasgupta
 * 	\date 	Jan 16, 2014
 */

#include <opencv2/opencv.hpp>
#include <string>

#include "Display.h"
#if 0
#include "vlc.h"
#endif

using namespace std;
using namespace cv;
#if 0
using namespace vlc;
#endif

namespace avp
{
	Display::Display()
	{
	}

	Display::Display(const string fileStr_pre_b, const string fileStr_post_b,const string dispStr_pre_b,const int firstCamNum_b, const int numDigitsInCamIdx_b,const int numCam_b,const float startFrFrac_b,const float endFrFrac_b,const int dispStart_x_b,const int dispStart_y_b)
	{
	       fileStr_pre = fileStr_pre_b;
	       fileStr_post = fileStr_post_b;
	       dispTitle_pre = dispStr_pre_b;
           firstCamNum = firstCamNum_b;
           numCam = numCam_b;
           numDigitsInCamIdx = numDigitsInCamIdx_b;
           dispStart_x = dispStart_x_b;
           dispStart_y = dispStart_y_b;
           startFrFrac = startFrFrac_b;
           endFrFrac = endFrFrac_b;
	}

	Display::Display(const string fileStr_pre_b, const string fileStr_post_b,const string dispStr_pre_b,const int firstCamNum_b, const int numCam_b,const int numDigitsInCamIdx_b,const float startFrFrac_b,const float endFrFrac_b,const int dispStart_x_b,const int dispStart_y_b,const int dispIncr_x_b,const int dispIncr_y_b)
	{
	       fileStr_pre = fileStr_pre_b;
	       fileStr_post = fileStr_post_b;
	       dispTitle_pre = dispStr_pre_b;
           firstCamNum = firstCamNum_b;
           numCam = numCam_b;
           numDigitsInCamIdx = numDigitsInCamIdx_b;
           dispStart_x = dispStart_x_b;
           dispStart_y = dispStart_y_b;
           dispIncr_x = dispIncr_x_b;
           dispIncr_y = dispIncr_y_b;
           startFrFrac = startFrFrac_b;
           endFrFrac = endFrFrac_b;

	}

	Display::Display(const string *camPath_b,const int *vWidth_b,const int *vHeight_b,const string dispStr_pre_b,const int firstCamNum_b, const int numCam_b,const int dispStart_x_b,const int dispStart_y_b,const int dispIncr_x_b,const int dispIncr_y_b,const string library_b)
	{
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
           library = library_b;

	}

	int Display::setup(const string fileStr_pre_b, const string fileStr_post_b,const string dispStr_pre_b,const int firstCamNum_b, const int numCam_b,const int numDigitsInCamIdx_b,const float startFrFrac_b,const float endFrFrac_b,const int dispStart_x_b,const int dispStart_y_b)
	{
	       fileStr_pre = fileStr_pre_b;
	       fileStr_post = fileStr_post_b;
	       dispTitle_pre = dispStr_pre_b;
           firstCamNum = firstCamNum_b;
           numCam = numCam_b;
           numDigitsInCamIdx = numDigitsInCamIdx_b;
           dispStart_x = dispStart_x_b;
           dispStart_y = dispStart_y_b;
           startFrFrac = startFrFrac_b;
           endFrFrac = endFrFrac_b;
           return 0;
	}

	int Display::setup(const string fileStr_pre_b, const string fileStr_post_b,const string dispStr_pre_b,const int firstCamNum_b, const int numCam_b,const int numDigitsInCamIdx_b,const float startFrFrac_b,const float endFrFrac_b,const int dispStart_x_b,const int dispStart_y_b,const int dispIncr_x_b,const int dispIncr_y_b)
	{
	       fileStr_pre = fileStr_pre_b;
	       fileStr_post = fileStr_post_b;
	       dispTitle_pre = dispStr_pre_b;
           firstCamNum = firstCamNum_b;
           numCam = numCam_b;
           numDigitsInCamIdx = numDigitsInCamIdx_b;
           dispStart_x = dispStart_x_b;
           dispStart_y = dispStart_y_b;
           dispIncr_x = dispIncr_x_b;
           dispIncr_y = dispIncr_y_b;
           startFrFrac = startFrFrac_b;
           endFrFrac = endFrFrac_b;
           return 0;
	}

	int Display::play_mem()
	{
	       if (numCam == 1)
	           playSingleVideo();
	       else
	    	   playMultVideos();
	       return 0;
	}
#if 0
	int Display::play_cam()
	{
	       if (numCam == 1)
	       {
	    	   if (library == "libvlc")
	    		   playNetCamVideo_vlc();
	    	   else if (library == "ffmpeg")
	    		   playNetCamVideo();
	       }
	       else
	       {
	    	   cout << "Yet to implement" << endl;
	       }
	       return 0;
	}
#endif
    int Display::playSingleVideo()
	{
        ostringstream convert2Str;
        convert2Str << firstCamNum;
        fileStr = fileStr_pre + convert2Str.str() + fileStr_post;
           cout << " playSingleVideo:: fileStr = " << fileStr << endl;
           cout << " playSingleVideo:: fileStr_post  = " << fileStr_post  << endl;
	    dispTitle = dispTitle_pre + convert2Str.str();
	    VideoCapture myVideo(fileStr);
	    Mat frame;
	    int key = 0;
	    int fps = myVideo.get(CV_CAP_PROP_FPS);
	    cout << "fps =  " << fps << endl;
	    int frWidth = (int)myVideo.get(CV_CAP_PROP_FRAME_WIDTH);
	    int frHeight = (int)myVideo.get(CV_CAP_PROP_FRAME_HEIGHT);
	    int numFr = (int)myVideo.get(CV_CAP_PROP_FRAME_COUNT);
	    int frNum = (int)myVideo.get(CV_CAP_PROP_POS_FRAMES);

        startFrNum = round(startFrFrac * numFr);
	    endFrNum = round(endFrFrac * numFr);
        cout << "SingleVideoDisplay: startFrNum = " << startFrNum << " endFrNum = " << endFrNum << endl;
	    cout << "Width =  " << frWidth << " Height = " << frHeight <<  " Number of Frames = " <<  numFr << " Frame Num = " << frNum <<  endl;
        myVideo.set(CV_CAP_PROP_POS_FRAMES,startFrNum);


        while(key != 'q')
	    {
            int frPos = (int)myVideo.get(CV_CAP_PROP_POS_FRAMES);

	        myVideo >> frame;

            if (frPos == endFrNum)
            {
                // Forcing loop to quit;
                key = 'q';
                break;
             }

    		imshow(dispTitle, frame);

            moveWindow(dispTitle,dispStart_x,dispStart_y);
		    key = waitKey(1000/fps);
            cout << "Frame # " << frPos << " from camera # " << firstCamNum  << endl;

        }


        waitKey(1000*10); //Wait for 5 seconds or till any key is pressed
	    myVideo.release();
	    destroyWindow(dispTitle);
	    cout << "Exiting ..." << endl;
	    return 0;
    }

    int Display::playNetCamVideo()
	{
        ostringstream convert2Str;
        convert2Str << firstCamNum;
	    dispTitle = dispTitle_pre + convert2Str.str();

		VideoCapture myVideo;
		Mat frame;

	    int key = 0;

		if(!myVideo.open(camPath[firstCamNum])) {
			cout << "Error opening video stream or file" << endl;
			return 0;
		}

	    int fps = myVideo.get(CV_CAP_PROP_FPS);
	    cout << "fps =  " << fps << endl;

		 while(key != 'q')
		 {
			if(!myVideo.read(frame)) {
				cout << "No frame" << endl;
				break;
			}

			imshow(dispTitle, frame);
            moveWindow(dispTitle,dispStart_x,dispStart_y);

		    key = waitKey(1000/fps);
		}

	    myVideo.release();
	    destroyWindow(dispTitle);
	    cout << "Exiting ..." << endl;

		return 0;

	}
#if 0
    int Display::playNetCamVideo_vlc()
    {
    	vlcClass camVideo(camPath,vWidth,vHeight,dispTitle_pre,firstCamNum,1,dispStart_x,dispStart_y,0,dispIncr_y);
    	camVideo.play();

	    int key = 0;
		while(key != 'q')
		    key = waitKey(1);

	    cout << "Exiting ..." << endl;
    	return 0;

    }
#endif
	int Display::playMultVideos()
	{
	    int camIdx;
	    string dispTitleArr[numCam];
	    string fileStrArr[numCam];
	    VideoCapture myVideo[numCam];
	    Mat videoFrame;
        int disp_x = dispStart_x,disp_y = dispStart_y;
        for ( camIdx = firstCamNum; camIdx < firstCamNum+numCam; camIdx++)
        {
            ostringstream convert2Str;
            convert2Str << camIdx;
            fileStrArr[camIdx] = fileStr_pre + convert2Str.str() + fileStr_post;
	        dispTitleArr[camIdx] = dispTitle_pre + convert2Str.str();

                fileStr = fileStr_pre + convert2Str.str() + fileStr_post;
	        myVideo[camIdx].open(fileStrArr[camIdx]);
        }
        cout << "Configured Input Video streams " << endl;

        // Get and display video properties based on first video file
        int key = 0;
        int fps = myVideo[0].get(CV_CAP_PROP_FPS);
        int frWidth = (int)myVideo[0].get(CV_CAP_PROP_FRAME_WIDTH);
        int frHeight = (int)myVideo[0].get(CV_CAP_PROP_FRAME_HEIGHT);
        int numFr = (int)myVideo[0].get(CV_CAP_PROP_FRAME_COUNT);
        int frNum = (int)myVideo[0].get(CV_CAP_PROP_POS_FRAMES);
        int frPos;
        cout << "fps =  " << fps << " Width =  " << frWidth << " Height = " << frHeight <<  " Number of Frames = " <<  numFr << " Frame Num = " << frNum <<  endl;

        // Adjust image size based on screen resolution
        int rs_frWidth = frWidth/4;
        int rs_frHeight = frHeight/4;
        //

	    startFrNum = round(startFrFrac * numFr);
	    endFrNum = round(endFrFrac * numFr);

	    cout << "Displaying from frame " <<  startFrNum << " to " << endFrNum <<  endl;

        for ( camIdx = firstCamNum; camIdx < firstCamNum+numCam; camIdx++)
        {
            myVideo[camIdx].set(CV_CAP_PROP_POS_FRAMES,startFrNum);

            namedWindow(dispTitleArr[camIdx],CV_WINDOW_NORMAL|CV_WINDOW_KEEPRATIO);
            moveWindow(dispTitleArr[camIdx],disp_x,disp_y);
            resizeWindow(dispTitleArr[camIdx],rs_frWidth,rs_frHeight);

            // display in two rows with appropriate spacing
            disp_x = camIdx == numCam/2 - 1 ? dispStart_x : disp_x + rs_frWidth + dispStart_x;
            disp_y = camIdx == numCam/2 - 1? disp_y + rs_frHeight + dispStart_y: disp_y;
        }

        // Now do a round-robin and display frames from all the cameras
        while(key != 'q')
        {
            disp_x = dispStart_x,disp_y = dispStart_y;
            for ( camIdx = firstCamNum; camIdx < firstCamNum+numCam; camIdx++)
            {
                frPos = (int)myVideo[camIdx].get(CV_CAP_PROP_POS_FRAMES);
                myVideo[camIdx] >> videoFrame;

                if (videoFrame.empty())
                {
                    cout << "End of data ... " << endl;
                    // Forcing loop to quit;
                    key = 'q';
                    break;
                }

                imshow(dispTitleArr[camIdx], videoFrame);

                key = waitKey(1000/fps);
                if (key == 'q')
                    break;
                cout << "Frame # " << frPos << " from camera # " << camIdx << " firstCamNum = " << firstCamNum << " numCam = " << numCam << endl;

                if ((frPos == endFrNum) && (camIdx == (firstCamNum+numCam -1)))
                {
                    // Forcing loop to quit;
                    key = 'q';
                    break;
                }
            }
        }

        waitKey(1000*10); //Wait for 5 seconds or till any key is pressed
        for ( camIdx = firstCamNum; camIdx < firstCamNum+numCam; camIdx++)
        {
            myVideo[camIdx].release();
	        destroyWindow(dispTitleArr[camIdx]);
        }
	    cout << "Exiting ..." << endl;
        return 0;
	}

}
