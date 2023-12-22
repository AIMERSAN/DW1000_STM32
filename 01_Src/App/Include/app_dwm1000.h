/**
  ******************************************************************************
  * @file    app_dwm1000.h
  * @author  YH
  * @version V1.0
  * @date    2023
  * @brief   dwm1000 测距功能处理头文件
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#ifndef __APP_DWM1000_H_
#define __APP_DWM1000_H_

#include "drv_Spi.h"

typedef signed long long int64;
typedef unsigned long long uint64;

/* 定义信道标号 */
#define MODULE_CHANNEL            5

#define TX_ANT_DLY                16436
#define RX_ANT_DLY                16436
#define RX_BUF_LEN                24
#define ALL_MSG_COMMON_LEN        10  /* 消息中的公共字节数据 */
#define ALL_MSG_SN_IDX            2   /* 帧中的特定字段 */
#define FINAL_MSG_POLL_TX_TS_IDX  10
#define FINAL_MSG_RESP_RX_TS_IDX  14
#define FINAL_MSG_FINAL_TX_TS_IDX 18
#define FINAL_MSG_TS_LEN          4
#define SEND_DATA_HIGH            11
#define SEND_DATA_LOW             12

/*
    Delay between frames, in UWB microseconds. See NOTE 4 below. 
    This is the delay from Frame RX timestamp to TX reply timestamp used for calculating/setting the DW1000's delayed TX function. 
    This includes the frame length of approximately 2.46 ms with above configuration.
 */
#define POLL_RX_TO_RESP_TX_DLY_UUS 2600   /* 回复时间延迟 */

/* This is the delay from the end of the frame transmission to the enable of the receiver, as programmed for the DW1000's wait for response feature. */
#define RESP_TX_TO_FINAL_RX_DLY_UUS 500

/* Receive final timeout. See NOTE 5 below. */
#define FINAL_RX_TIMEOUT_UUS 3300   /* 最终超时 */

/* 
    UWB microsecond (uus) to device time unit (dtu, around 15.65 ps) conversion factor.
    1 uus = 512 / 499.2 ? and 1 ? = 499.2 * 128 dtu. 
*/
#define UUS_TO_DWT_TIME 65536
#define SPEED_OF_LIGHT  299702547  /* 光速 */

void Dwm1000DeviceInit(void);
void Dwm1000Respond(double *dis);



#endif
