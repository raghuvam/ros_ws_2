
#ifndef MAIN_H
#define MIAN_H
//#include <linux/examples/tda2xx/include/chains.h>
//#include <linux/examples/tda2xx/include/chains_common.h>
//#include <linux/src/links/null/nullLink_priv.h>
//#include <include/link_api/system_inter_link_api.h>
//#include <include/link_api/nullLink.h>
#include <string.h>

int VisionSDK_main();

typedef struct {
    int tskId;
    /**< Placeholder to store null link task id */

    int recvCount;
    /**< Count of buffers received */

    FILE *fpDataStream;
    /**< Binary File for the bitsream stream data.*/

} StreamerLink_Obj;


/**
 *******************************************************************************
 *
 *  StreamerLink_BitstreamBuffer has bitsstream data from vision SDK, this object
 helps to pass params from system_BitsstreamBuffer of vision SDK code to ROS
 image publisher function. Initialise this obj in framerStreamHandler() function
 of the usecase file and copy the params from system_BitsstreamBuffer.
 *
 *******************************************************************************
 */
typedef struct {

    void *bufAddr;
    /**< when NULL bitstream data is not present,
     *      meta data could still be present */

    int bufSize;
    /**< Total buffer size */

    int fillLength;
    /**< size of valid data inside the buffer */

    void *metaBufAddr;
    /**< Metadata buffer address when NULL meta data is not present */

    int metaBufSize;
    /**< meta buffer size */

    int metaFillLength;
    /**< size of valid data inside the meta data buffer  */

    int flags;
    /**< see SYSTEM_BITSTREAM_BUFFER_FLAG_* */

    int width;
    /**< Width of frame encoded inside the bitstream */

    int height;
    /**< Height of frame encoded inside the bitstream */

} StreamerLink_BitstreamBuffer;

int framePublisher(StreamerLink_BitstreamBuffer* bitstreamBuffer, StreamerLink_Obj* pObj);

#endif











