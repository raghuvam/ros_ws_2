/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \file chains_vipSingleCameraView.c
 *
 * \brief  Usecase file implementation of capture display usecase.
 *
 *         Usecase file for single camere view usecase.
 *
 *         Capture --> Encode --> Null Link(A15)
 *
 *
 *         In this use-case we capture 1 CH of video from OV1063x 720p30, encode,
 *         and send it to A15 using IPC_OUT, IPC_IN. The A15 implements the NULL link which
 *         terminates the data flow
 *
 *         The data flow daigram is shown below
 *
 *             Capture (VIP) 1CH 30fps 1280x720 or 60fp 1920x1080
 *                   |
 *             Encode (MJPEG) 1CH - bitstream
 *                   |
 *                 IPC OUT
 *                   |
 *                 IPC IN
 *                   |
 *                NULL (A15)
 *
 * \version 0.0 (Jul 2014) : [PN] First version ported for linux.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <linux/examples/tda2xx/include/chains.h>
#include <linux/examples/tda2xx/include/chains_common.h>
#include <linux/src/links/null/nullLink_priv.h>
#include <include/link_api/nullLink.h>


#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)
#define MAX_NUMBER_OF_CHANNELS    (1)
#define ENCDEC_MAX_FRAME_WIDTH    (CAPTURE_SENSOR_WIDTH)
#define ENCDEC_MAX_FRAME_HEIGHT   (CAPTURE_SENSOR_HEIGHT)

#define MAX_INPUT_STR_SIZE  (80)

Chains_Ctrl gChains_usecaseCfg;

/**
 *******************************************************************************
 * \brief Max Size of the input string in characters.
 *******************************************************************************
 */


/**
 *******************************************************************************
 * \brief Run Time Test Menu string.
 *******************************************************************************
 */
char gChains_testMenu[] = {
    "\r\n "
    "\r\n ========="
    "\r\n Test Menu"
    "\r\n ========="
    "\r\n 1: 1CH VIP capture + SGX DISPLAY(A15)"
    "\r\n 2: 1CH VIP capture + Encode + Decode + SGX DISPLAY(A15)"
    "\r\n 3: 4CH VIP LVDS capture + SGX DISPLAY(A15)"
    "\r\n 4: 4CH AVB Capture + Decode + SGX DISPLAY(A15)"
    "\r\n 5: 1CH VIP caputre + Encode + Null Link"
    "\r\n 6: h264 Video Streamer"
    "\r\n "
    "\r\n p: CPU Status"
    "\r\n i: Show IP Addr (IPU + NDK + AVB) "
    "\r\n "
    "\r\n x: Exit "
    "\r\n z: Exit - AND SHUTDOWN Remote CPUs"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "



};

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char gChains_runTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Read a charater from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
char Chains_readChar()
{
    Int8 ch[80];

    fflush(stdin);
    fgets((char*)ch, MAX_INPUT_STR_SIZE, stdin);
    if(ch[1] != '\n' || ch[0] == '\n')
    ch[0] = '\n';

    return ch[0];
}


/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection
 *
 *          This functions displays the run time options available
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *******************************************************************************
*/
char Chains_menuRunTime()
{
    Vps_printf(gChains_runTimeMenu);

    return Chains_readChar();
}






/**
 *******************************************************************************
 *
 *  \brief  SingleCameraViewObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {
    /**< Link Id's and device IDs to use for this use-case */
    UInt32              appCtrlLinkId;
    UInt32              captureLinkId;
    UInt32              ipcOutLink_IPU1_0_Id;
    UInt32              ipcInLink_CPU_Id;
    UInt32              nullLinkId;
    UInt32              encodeLinkId;

    /**< Link create params and device create params to use for this use-case */
    CaptureLink_CreateParams                capturePrm;
    IpcLink_CreateParams                    ipcOutLink_IPU1_0_Prms;
    IpcLink_CreateParams                    ipcInLink_CPU_Prms;
    NullLink_CreateParams                   nullLinkPrm;
    EncLink_CreateParams                    encodePrm;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

} Chains_VipSingleCamEncNullObj;

/**
 *******************************************************************************
 *
 * \brief   Set Link Id's
 *
 *          This function is called to set the linkId,
 *          LinkId are assigned depending on which core
 *          link is expected to run.
 *          For IPC link ID is set using macro XXX_X_LINK
 *          where XXX_X is core on which the link is to created
 *          eg IPU1_0_LINK is for ipc link on ipu.
 *          LinkId can also be made using SYSTEM_MAKE_LINK_ID macro
 *          which takes ProcId as input param on which the link id is created.
 *
 *
 * \param   pObj [IN]  object of Chains_VipSingleCamEncNullObj type
 *
 *******************************************************************************
*/
static Void Chains_VipSingleCamEncNull_SetLinkId(
                                  Chains_VipSingleCamEncNullObj *pObj)
{
    pObj->captureLinkId = SYSTEM_LINK_ID_CAPTURE;

    pObj->ipcOutLink_IPU1_0_Id  = SYSTEM_LINK_ID_INVALID;
    pObj->ipcInLink_CPU_Id      = SYSTEM_LINK_ID_INVALID;

    pObj->ipcOutLink_IPU1_0_Id  = IPU1_0_LINK(SYSTEM_LINK_ID_IPC_OUT_0);
    pObj->ipcInLink_CPU_Id      =
         SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_A15_0, SYSTEM_LINK_ID_IPC_IN_0);

    pObj->nullLinkId   = A15_0_LINK(SYSTEM_LINK_ID_NULL_0);
    pObj->encodeLinkId = SYSTEM_LINK_ID_VENC_0;
}

/**
 *******************************************************************************
 *
 * \brief   Reset Link Create Parameters
 *
 *          Set the default Create Params for capture and display create params
 *          This function is called in create before setting the Link params
 *          so that all default params are assigned.
 *          All the Link_CreateParams_Init is called from this function.
 *          It ensures no junk value getting assigned.
 *
 * \param   pObj      [IN]   object of Chains_VipSingleCamEncNullObj type
 *
 *******************************************************************************
*/
static Void Chains_VipSingleCamEncNull_ResetLinkPrms(
                                  Chains_VipSingleCamEncNullObj *pObj)
{
    CaptureLink_CreateParams_Init(&pObj->capturePrm);
    IpcLink_CreateParams_Init(&pObj->ipcOutLink_IPU1_0_Prms);
    IpcLink_CreateParams_Init(&pObj->ipcInLink_CPU_Prms);
    NullLink_CreateParams_Init(&pObj->nullLinkPrm);
    EncLink_CreateParams_Init(&pObj->encodePrm);
}

/**
 *******************************************************************************
 *
 * \brief   Set Capture Create Parameters
 *
 *          This function is used to set the capture params.
 *          It is called in Create function. It is advisable to have
 *          Chains_VipSingleCamEncNull_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *          Capture Link Input,Output, Vip parameters are set here.
 *
 * \param   pPrm         [IN]  CaptureLink_CreateParams
 *
 *******************************************************************************
*/
static Void Chains_VipSingleCamEncNull_SetCapturePrms(
                                  CaptureLink_CreateParams *pPrm,
                                  UInt32 captureOutWidth,
                                  UInt32 captureOutHeight,
                                  Chains_CaptureSrc captureSrc
                                  )
{
    UInt32 i, streamId;

    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrms;
    CaptureLink_VipPortConfig    *pPortCfg;

    memset(pPrm, 0, sizeof(*pPrm));
    /* For SCV usecase number of camera is always 1 */
    pPrm->numVipInst = 1;

    for (i=0; i<SYSTEM_CAPTURE_INST_MAX; i++)
    {
        pInstPrm = &pPrm->vipInst[i];
        pInprms = &pInstPrm->inParams;
        pInstPrm->vipInstId     =   i;
        if(captureSrc == CHAINS_CAPTURE_SRC_OV10635)
        {


            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   CAPTURE_SENSOR_WIDTH;
            pInprms->height     =   CAPTURE_SENSOR_HEIGHT;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        }
        else if (captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P)
        {


            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   CAPTURE_SENSOR_WIDTH;
            pInprms->height     =   CAPTURE_SENSOR_HEIGHT;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        }
        else if (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P)
        {


            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   1920;
            pInprms->height     =   1080;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }
        else
        {
            /* Nothing here. To avoid MISRA C warnings */
        }


        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   CAPTURE_SENSOR_WIDTH;
            pOutprms->height        =   CAPTURE_SENSOR_HEIGHT;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV420SP_UV;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;
            if((pInprms->width != pOutprms->width) ||
                (pInprms->height != pOutprms->height))
            {
                pOutprms->scEnable      =   TRUE;
            }
            else
            {
                pOutprms->scEnable      =   FALSE;
            }
            pOutprms->subFrmPrms.subFrameEnable = FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0;

        }
        pScPrms = &pInstPrm->scPrms;
        pScPrms->inCropCfg.cropStartX = 0;
        pScPrms->inCropCfg.cropStartY = 0;
        pScPrms->inCropCfg.cropWidth = pInprms->width;
        pScPrms->inCropCfg.cropHeight = pInprms->height;

        pScPrms->scCfg.bypass       = FALSE;
        pScPrms->scCfg.nonLinear    = FALSE;
        pScPrms->scCfg.stripSize    = 0;

        pScPrms->userCoeff = FALSE;

        /* pScPrms->scCoeffCfg is not reuquired in case
         * pScPrms->userCoeff is FALSE
         */
        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   FALSE;



        pPortCfg->intfCfg.clipActive    =   FALSE;
        pPortCfg->intfCfg.clipBlank     =   FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0;
        pPortCfg->disCfg.fidSkewPreCnt      =   0;
        pPortCfg->disCfg.lineCaptureStyle   =
                                SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.discreteBasicMode  =   TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
                                SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        pPortCfg->comCfg.invertFidPol       =   FALSE;
        pPortCfg->comCfg.enablePort         =   FALSE;
        pPortCfg->comCfg.expectedNumLines   =   pInprms->height;
        pPortCfg->comCfg.expectedNumPix     =   pInprms->width;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;
        pPortCfg->actCropEnable             =   TRUE;

        if ((captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
            (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
        {
            pPortCfg->actCropEnable         =   FALSE;
        }

        pPortCfg->actCropCfg.srcNum                     =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->actCropCfg.cropCfg.cropWidth          =   pInprms->width;
        pPortCfg->actCropCfg.cropCfg.cropHeight         =   pInprms->height;

        pPortCfg->ancCropCfg.srcNum                     =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0;

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set IPC Create Parameters
 *
 *          It is called in Create function.
 *          In this function ipc link params are set
 *          Ipc link operates in 2 modes , polling and interrupt.
 *          The mode is set depending on the usecase configuration.
 *
 * \param   pPrm    [IN]    IpcLink_CreateParams
 *
 *******************************************************************************
*/
static Void Chains_VipSingleCamEncNull_SetIPCPrms(
                                  IpcLink_CreateParams *prm, Bool enableMode)
{
    prm->enablePollingMode = enableMode;
}

/**
 *******************************************************************************
 *
 * \brief   Set NULL Link Parameters
 *
 *          It is called in Create function.

 *
 * \param   pPrm    [IN]    IpcLink_CreateParams
 *
 *******************************************************************************
*/
static Void Chains_VipSingleCamEncNull_SetNullLinkPrms(
                                 NullLink_CreateParams *prm, Bool enableMode)
{
    prm->numInQue = 1;
    prm->dumpDataType = NULL_LINK_COPY_TYPE_BITSTREAM_FILE;
    strcpy(prm->nameDataFile, "./test.h264");
    (Void) enableMode;
}

/**
 *******************************************************************************
 *
 * \brief   Set Enc Create Parameters
 *
 * \param   pPrm         [IN]  EncLink_CreateParams
 *
 *******************************************************************************
*/
static Void Chains_VipSingleCamEncNull_SetEncPrms(
                                                EncLink_CreateParams *pPrm)
{
    int i, chId;
    EncLink_ChCreateParams *pLinkChPrm;
    EncLink_ChDynamicParams *pLinkDynPrm;

    for (i = 0; i < ENC_LINK_MAX_BUF_ALLOC_POOLS; i++)
    {
        pPrm->numBufPerCh[i] = 4;
    }

    for (chId = 0; chId < MAX_NUMBER_OF_CHANNELS; chId++)
    {
        pLinkChPrm  = &pPrm->chCreateParams[chId];
        pLinkDynPrm = &pLinkChPrm->defaultDynamicParams;

        UTILS_assert (chId < ENC_LINK_MAX_CH);
        {
            pLinkChPrm->format                 = SYSTEM_IVIDEO_MJPEG;
            pLinkChPrm->profile                = 0;
            pLinkChPrm->dataLayout             = VENC_FIELD_SEPARATED;
            pLinkChPrm->fieldMergeEncodeEnable = FALSE;
            pLinkChPrm->enableAnalyticinfo     = 0;
            pLinkChPrm->enableWaterMarking     = 0;
            pLinkChPrm->maxBitRate             = 0;
            pLinkChPrm->encodingPreset         = 0;
            pLinkChPrm->rateControlPreset      = 0;
            pLinkChPrm->enableHighSpeed        = 0;
            pLinkChPrm->enableSVCExtensionFlag = 0;
            pLinkChPrm->numTemporalLayer       = 0;
            pLinkChPrm->overrideInputScanFormat= 0;
            pLinkChPrm->fieldPicEncode         = 0;

            pLinkDynPrm->intraFrameInterval    = 0;
            pLinkDynPrm->targetBitRate         = 100*1000*30;
            pLinkDynPrm->interFrameInterval    = 0;
            pLinkDynPrm->mvAccuracy            = 0;
            pLinkDynPrm->inputFrameRate        = 30;
            pLinkDynPrm->rcAlg                 = 0;
            pLinkDynPrm->qpMin                 = 0;
            pLinkDynPrm->qpMax                 = 0;
            pLinkDynPrm->qpInit                = -1;
            pLinkDynPrm->vbrDuration           = 0;
            pLinkDynPrm->vbrSensitivity        = 0;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Connect the Links
 *
 *          Function sets the NextLink and Previous Link Id's
 *          This function is called in Chains_VipSingleCamEncNull_Create,
 *          When all the link parameters are set the links are connected.
 *          the next linkId , previous linkId and queueId are
 *          set depending on the usecase.
 *          Ipc Links are required only if ALG link is enabled on other core.
 *
 * \param   pObj     [IN] Object of Chains_VipSingleCamEncNullObj type
 *
 *******************************************************************************
*/
static Void Chains_VipSingleCamEncNull_ConnectLinks(
                                  Chains_VipSingleCamEncNullObj *pObj)
{


    pObj->capturePrm.outQueParams.nextLink = pObj->encodeLinkId;
    pObj->encodePrm.inQueParams.prevLinkId    = pObj->captureLinkId;
    pObj->encodePrm.inQueParams.prevLinkQueId = 0;

    pObj->encodePrm.outQueParams.nextLink = pObj->ipcOutLink_IPU1_0_Id;

    pObj->ipcOutLink_IPU1_0_Prms.inQueParams.prevLinkId =
                                                    pObj->encodeLinkId;
    pObj->ipcOutLink_IPU1_0_Prms.inQueParams.prevLinkQueId = 0;

    pObj->ipcOutLink_IPU1_0_Prms.outQueParams.nextLink =
                                                    pObj->ipcInLink_CPU_Id;
    pObj->ipcInLink_CPU_Prms.inQueParams.prevLinkId =
                                                pObj->ipcOutLink_IPU1_0_Id;
    pObj->ipcInLink_CPU_Prms.inQueParams.prevLinkQueId = 0;

    pObj->ipcInLink_CPU_Prms.outQueParams.nextLink = pObj->nullLinkId;
    pObj->nullLinkPrm.inQueParams[0].prevLinkId    = pObj->ipcInLink_CPU_Id;
    pObj->nullLinkPrm.inQueParams[0].prevLinkQueId = 0;
}

/**
 *******************************************************************************
 *
 * \brief   Creates the links by the usecase
 *
 *          Function sets all the create params for the links
 *          Link Create is called with the create params and control cmd
 *          is passed to links if required
 *          LinkId's are set parameters of link are reset.
 *          Links are connected after all params are set .
 *          System_linkCreate is called for links with LinkId and create params.
 *
 * \param   pObj          [IN]  Chains_VipSingleCamEncNullObj
 *
 * \param   chainsCfg     [IN]  Chains_Ctrl
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 Chains_VipSingleCamEncNull_Create(
                                   Chains_VipSingleCamEncNullObj *pObj,
                                   Chains_Ctrl *chainsCfg)
{
    Int32 status;
    Chains_VipSingleCamEncNull_SetLinkId(pObj);
    Chains_VipSingleCamEncNull_ResetLinkPrms(pObj);

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    Chains_VipSingleCamEncNull_SetCapturePrms(&pObj->capturePrm,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            chainsCfg->captureSrc
            );

    Chains_VipSingleCamEncNull_SetEncPrms(&pObj->encodePrm);

    Chains_VipSingleCamEncNull_SetIPCPrms
	                    (&pObj->ipcOutLink_IPU1_0_Prms, chainsCfg->pollingMode);
    Chains_VipSingleCamEncNull_SetIPCPrms
                    (&pObj->ipcInLink_CPU_Prms, chainsCfg->pollingMode);
    Chains_VipSingleCamEncNull_SetNullLinkPrms
                    (&pObj->nullLinkPrm, chainsCfg->pollingMode);

    Chains_VipSingleCamEncNull_ConnectLinks(pObj);

    status = System_linkCreate(pObj->captureLinkId,
                                &pObj->capturePrm,
                                sizeof(pObj->capturePrm));
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkCreate(pObj->encodeLinkId,
                                &pObj->encodePrm,
                                sizeof(pObj->encodePrm));
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkCreate(pObj->ipcOutLink_IPU1_0_Id,
                                &pObj->ipcOutLink_IPU1_0_Prms,
                                sizeof(pObj->ipcOutLink_IPU1_0_Prms));
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkCreate(pObj->ipcInLink_CPU_Id,
                            &pObj->ipcInLink_CPU_Prms,
                            sizeof(pObj->ipcInLink_CPU_Prms));
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkCreate(pObj->nullLinkId,
                                &pObj->nullLinkPrm,
                                sizeof(pObj->nullLinkPrm));
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Start the Links
 *
 *          Function sends a control command to links to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_VipSingleCamEncNullObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 Chains_VipSingleCamEncNull_Start(
                                   Chains_VipSingleCamEncNullObj *pObj,
                                   Chains_Ctrl *chainsCfg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_OV10635)
    {
        AppCtrlCmd_VideoSensorCreateAndStartPrm vidSensorPrm;

        vidSensorPrm.sensorId = APP_CTRL_VID_SENSOR_OV10635;
        vidSensorPrm.isLVDSCaptMode = FALSE;
        vidSensorPrm.numLvdsCh = 1;

        status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                    APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                                    &vidSensorPrm,
                                    sizeof(AppCtrlCmd_VideoSensorCreateAndStartPrm),
                                    TRUE);
    }
    else if((chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
        (chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
    {
        status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                    APP_CTRL_LINK_CMD_HDMI_RX_CREATE_AND_START,
                                    NULL,
                                    0,
                                    TRUE);

    }
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkStart(pObj->nullLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkStart(pObj->ipcInLink_CPU_Id);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkStart(pObj->ipcOutLink_IPU1_0_Id);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkStart(pObj->encodeLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkStart(pObj->captureLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Stop the Links
 *
 *          Function sends a control command to links to
 *          to Stop all the prior created links and sensor .
 *          Stop is called in reverse order of the chain as the consumed
 *          buffers need to be returned to the previous components.
 *          System_linkStop is called with LinkId to stop the links.
 *
 * \param   pObj   [IN]  Chains_VipSingleCamEncNullObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 Chains_VipSingleCamEncNull_Stop(
                                   Chains_VipSingleCamEncNullObj *pObj,
                                   Chains_Ctrl *chainsCfg)
{

    Int32 status;

    status = System_linkStop(pObj->ipcInLink_CPU_Id);
    OSA_assert(status==0);

    status = System_linkStop(pObj->ipcOutLink_IPU1_0_Id);
    OSA_assert(status==0);

    status = System_linkStop(pObj->captureLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkStop(pObj->encodeLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkStop(pObj->nullLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    if(chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_OV10635)
    {

        status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                    APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE,
                                    NULL,
                                    0,
                                    TRUE);
    }
    else if((chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
        (chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
    {
        status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                    APP_CTRL_LINK_CMD_HDMI_RX_STOP_AND_DELETE,
                                    NULL,
                                    0,
                                    TRUE);
    }
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Delete the Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   Chains_VipSingleCamEncNullObj
 *
 *******************************************************************************
*/
static Int32 Chains_VipSingleCamEncNull_Delete(
                                   Chains_VipSingleCamEncNullObj *pObj,
                                   Chains_Ctrl *chainsCfg)
{
    Int32 status;

    status = System_linkDelete(pObj->captureLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkDelete(pObj->encodeLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkDelete(pObj->ipcInLink_CPU_Id);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkDelete(pObj->ipcOutLink_IPU1_0_Id);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkDelete(pObj->nullLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Print Link Buffer Statistics
 *
 *          Function sends a control command to capture and display link to
 *          to print the buffer statistics.
 *          System_linkPrintBufferStatistics is called with linkId to print
 *          the buffer statistics. A delay of 500ms is introduced for print
 *          command between cores to ensure logs are printed in order.
 *
 * \param   pObj    [IN]   Chains_VipSingleCamEncNullObj
 *
 *******************************************************************************
*/
static void Chains_VipSingleCamEncNull_printBufferStatistics(
                                  Chains_VipSingleCamEncNullObj *pObj)
{
    System_linkPrintBufferStatistics(pObj->captureLinkId);
    System_linkPrintBufferStatistics(pObj->encodeLinkId);

    System_linkPrintBufferStatistics(pObj->ipcOutLink_IPU1_0_Id);
    /* Task sleep delay is introduced to allow printing to complete */
    usleep(500);

    System_linkPrintBufferStatistics(pObj->ipcInLink_CPU_Id);
    System_linkPrintBufferStatistics(pObj->nullLinkId);
}

/**
 *******************************************************************************
 *
 * \brief   Print Link Statistics
 *
 *          Function sends a control command to capture and display link to
 *          to print the statistics
 *          System_linkPrintStatistics is called with linkId to print
 *          the link performance statistics.
 *          A delay of 500ms is introduced for print command between
 *          cores to ensure logs are printed in order.
 *
 * \param   pObj    [IN]  Chains_VipSingleCamEncNullObj
 *
 *******************************************************************************
*/
static void Chains_VipSingleCamEncNull_PrintStatistics(
                                  Chains_VipSingleCamEncNullObj *pObj)
{

    System_linkPrintStatistics(pObj->captureLinkId);
    System_linkPrintStatistics(pObj->encodeLinkId);
    System_linkPrintStatistics(pObj->ipcOutLink_IPU1_0_Id);
    usleep(500);

    System_linkPrintStatistics(pObj->ipcInLink_CPU_Id);
    System_linkPrintStatistics(pObj->nullLinkId);

}

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_VipSingleCamEncNull(Chains_Ctrl *chainsCfg)
{   
    char ch;
    UInt32 done = FALSE;
    Chains_VipSingleCamEncNullObj chainsObj;
    Vps_printf("test :raghu 0");

    ChainsCommon_statCollectorReset();
Vps_printf("test :raghu 1");
    ChainsCommon_memPrintHeapStatus();
	Vps_printf("test :raghu 2");
    Chains_VipSingleCamEncNull_Create(&chainsObj, chainsCfg);
Vps_printf("test :raghu 3");
    ChainsCommon_memPrintHeapStatus();
Vps_printf("test :raghu 4");
    Chains_VipSingleCamEncNull_Start(&chainsObj,chainsCfg);
Vps_printf("test :raghu 5");
    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);
Vps_printf("test :raghu 6");
    while(!done)
    {
        ch = Chains_menuRunTime();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'p':
            case 'P':
                Chains_VipSingleCamEncNull_PrintStatistics(&chainsObj);
		Vps_printf("test :raghu 7");
                Chains_VipSingleCamEncNull_printBufferStatistics(&chainsObj);
		Vps_printf("test :raghu 8");
                ChainsCommon_prfCpuLoadPrint();
		Vps_printf("test :raghu 9");
                ChainsCommon_statCollectorPrint();
		Vps_printf("test :raghu 10");
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }


    Chains_VipSingleCamEncNull_Stop(&chainsObj,chainsCfg);
    Vps_printf("test :raghu 11");
    Chains_VipSingleCamEncNull_Delete(&chainsObj, chainsCfg);
Vps_printf("test :raghu 12");
    ChainsCommon_prfLoadCalcEnable(FALSE, FALSE, FALSE);
Vps_printf("test :raghu 13");
    ChainsCommon_memPrintHeapStatus();
Vps_printf("test :raghu 14");

}


int VisionSDK_main()
{
    Char ch;
    Bool shutdownRemoteCores = FALSE;
    System_init();
     Vps_printf("raghu test :1");
    ChainsCommon_appCtrlCommonInit();
     Vps_printf("raghu test :2");
    /* allow remote prints to complete, before showing main menu */
    OSA_waitMsecs(500);
        Vps_printf("raghu test :3");
    while(1)
    {
        Vps_printf(gChains_testMenu);
        ch = getchar();

        if(ch=='x')
            break;

        if(ch=='z')
        {
            shutdownRemoteCores = TRUE;
            break;
        }

        switch(ch)
        {
           

	    case '5':
                Chains_Ctrl_Init(&gChains_usecaseCfg);
		Vps_printf(" compilation test : raghu");        
		Chains_VipSingleCamEncNull(&gChains_usecaseCfg);
                break;
            case '2':
                Chains_Ctrl_Init(&gChains_usecaseCfg);
                chains_vipSingleCam_Enc_Dec_SgxDisplay(&gChains_usecaseCfg);
                break;
	    case '1':
                Chains_Ctrl_Init(&gChains_usecaseCfg);
                chains_vipSingleCam_SgxDisplay(&gChains_usecaseCfg);
                break;

	    
/*
            case '6':
		Chains_Ctrl_Init(&gChains_usecaseCfg);
                testH264VideoStreamer();
                break;



            case '3':
                Chains_Ctrl_Init(&gChains_usecaseCfg);
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV1063X;
                chains_lvdsVipMultiCam_SgxDisplay(&gChains_usecaseCfg);
                break;
            case '4':
                Chains_Ctrl_Init(&gChains_usecaseCfg);
                gChains_usecaseCfg.numLvdsCh = 4;
                Chains_AvbRxDecodeSgxDisplay(&gChains_usecaseCfg);
                break;

raghu
            
*/
            case 'p':
                ChainsCommon_printCpuStatus();
                break;
            case 'i':
                if(System_isProcEnabled(SYSTEM_PROC_IPU1_0))
                {
                    SystemCommon_IpAddr ipuIpAddr;
                    System_linkControl(
                        SYSTEM_LINK_ID_IPU1_0,
                        SYSTEM_COMMON_CMD_GET_IP_ADDR,
                        &ipuIpAddr,
                        sizeof(SystemCommon_IpAddr),
                        TRUE
                    );
                    Vps_printf(" Network IP address : %s\n", ipuIpAddr.ipAddr);
                }
                break;
        }
    }
    ChainsCommon_appCtrlCommonDeInit();
    System_deInit(shutdownRemoteCores);

    return 0;
}

