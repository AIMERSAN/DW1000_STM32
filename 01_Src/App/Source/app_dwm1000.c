/**
  ******************************************************************************
  * @file    app_dwm1000.c
  * @author  YH
  * @version V1.0
  * @date    2023
  * @brief   dwm1000 测距功能处理源文件
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include <string.h>

#include "app_dwm1000.h"
#include "bsp_DWM1000.h"
#include "deca_sleep.h"
#include "deca_device_api.h"
#include "deca_regs.h"

/* dwt communication configuration. */
static dwt_config_t dwtCommConfig = 
{
    MODULE_CHANNEL,               /* Channel number. */
    DWT_PRF_64M,     /* Pulse repetition frequency. */
    DWT_PLEN_1024,   /* Preamble length. */
    DWT_PAC32,       /* Preamble acquisition chunk size. Used in RX only. */
    0,               /* TX preamble code. Used in TX only. */
    0,               /* RX preamble code. Used in RX only. */
    1,               /* Use non-standard SFD (Boolean) */
    DWT_BR_110K,     /* Data rate. */
    DWT_PHRMODE_STD, /* PHY header mode. */
    (1025 + 64 - 32) /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
};

static uint32 statusReg = 0;        /* 存储状态寄存器的值用于断点检查 */
static uint8  rxBuffer[RX_BUF_LEN]; /* 接收数据缓冲区 */
static uint8  rxPolMlsg[]  = {0x41, 0x88, 0, 0xCA, 0xDE, 'W', 'A', 'V', 'E', 0x21, 0, 0}; /* 测距使用帧段*/
static uint8  txRespMsg[]  = {0x41, 0x88, 0, 0xCA, 0xDE, 'V', 'E', 'W', 'A', 0x10, 0x02, 0, 0, 0, 0};
static uint8  rxFinalMsg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'W', 'A', 'V', 'E', 0x23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint64 pollRxTs;             /* 接收时间缓存变量 */
static uint64 respTxTs;             /* 发送时间 */
static uint64 finalRxTs;            /* 后接收时间 */
static uint8  frameSeqNb = 0;       /* 帧序号，每次传递后递增 */
static double tof;                  /* 飞行时间 */

static uint64 getRxTimeStampU64(void)
{
    uint8_t tsTab[5];
    uint64  ts = 0;
    int i;

    dwt_readrxtimestamp(tsTab);
    for(i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |= tsTab[i];
    }
    return ts;
}

/* Ts - TimeStamp */
static uint64 getTxTimeStampU64(void)
{
    uint8_t tsTab[5];
    uint64  ts = 0;
    int i;
    dwt_readtxtimestamp(tsTab);
    for(i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |=  tsTab[i];
    }
    return ts;
}

static void finalMsgGetTs(const uint8_t *tsField, uint32 *ts)
{   
    int i;
    *ts = 0;
    for(i = 0; i < FINAL_MSG_TS_LEN; i++)
    {
        *ts += tsField[i] << (i * 8);
    }
}

void Dwm1000DeviceInit(void)
{   
    Dwm1000SpiInit();
    
    deca_sleep(10);

    Dwm1000Reset();

    /* 睡眠延时 */
    deca_sleep(2);

    Dwm1000SetBaudRate(DWM1000_LOWSPIBaudRate);

    /* 校正DWM1000，返回-1说明初始化没有成功 */
    while(dwt_initialise(DWT_LOADUCODE) == -1);

    Dwm1000SetBaudRate(DWM1000_HIGHSPIBaudRate);

    dwt_configure(&dwtCommConfig);

    dwt_setrxantennadelay(RX_ANT_DLY);

    dwt_setrxantennadelay(TX_ANT_DLY);
}


/**
* @brief  基站答复标签任务处理
* @param  double *dis 上一次测距的结果，
* @retval None
**/
void Dwm1000Respond(double *dis)
{
    dwt_setrxtimeout(0);
    dwt_rxenable(0);

    while (!((statusReg = dwt_read32bitreg(SYS_STATUS_ID)) & 
            (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_ERR)));/* 记录状态寄存器的值并轮询错误信息 */
    if(statusReg & SYS_STATUS_RXFCG)
    {
        static uint32 frameLen;
        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_RXFCG);
        frameLen = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFL_MASK_1023;
        if(frameLen <= RX_BUFFER_LEN)
        {
            dwt_readrxdata(rxBuffer, frameLen, 0);
        }
        rxBuffer[ALL_MSG_SN_IDX] = 0;
    
        if(memcmp(rxBuffer, rxPolMlsg, ALL_MSG_COMMON_LEN) == 0)//轮询 DS TWR发起者 验证公共字节是否相同
		{
            /* 声明 */
			uint32 resp_tx_time;
			pollRxTs = getRxTimeStampU64();//获取接收时间
			resp_tx_time = (pollRxTs + (POLL_RX_TO_RESP_TX_DLY_UUS * UUS_TO_DWT_TIME)) >> 8;
			dwt_setdelayedtrxtime(resp_tx_time);//设置发送响应时间			
			dwt_setrxaftertxdelay(RESP_TX_TO_FINAL_RX_DLY_UUS);
			dwt_setrxtimeout(FINAL_RX_TIMEOUT_UUS);//设置最终消息接收的预期延迟与超时
			txRespMsg[ALL_MSG_SN_IDX] = frameSeqNb;

			/************************************************************/
			*dis *= 100;
			if(*dis < 0) *dis=-*dis;
			txRespMsg[SEND_DATA_HIGH]=(u16)*dis>>8;//将上次测距数据发过去
			txRespMsg[SEND_DATA_LOW]=(u16)*dis;

			/*************************************************************/
			dwt_writetxdata(sizeof(txRespMsg), txRespMsg, 0);
			dwt_writetxfctrl(sizeof(txRespMsg), 0);
			dwt_starttx(DWT_START_TX_DELAYED | DWT_RESPONSE_EXPECTED);//编写并发送响应消息		
			while (!((statusReg = dwt_read32bitreg(SYS_STATUS_ID)) & (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_ERR)));//记录状态寄存器的值并轮询错误信息 等待接收数据
            frameSeqNb++;//帧序号递增
			if (statusReg & SYS_STATUS_RXFCG)//如果接受机正常
			{
				dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_RXFCG | SYS_STATUS_TXFRS);//清除RX TX帧事件
				frameLen = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFLEN_MASK;//接收帧
				if (frameLen <= RX_BUF_LEN)
				{
					dwt_readrxdata(rxBuffer, frameLen, 0);
				}
				rxBuffer[ALL_MSG_SN_IDX] = 0;//清除不相关字段简化验证
				if(memcmp(rxBuffer, rxFinalMsg, ALL_MSG_COMMON_LEN) == 0)//轮询 DS TWR发起者
				{
					uint32 poll_tx_ts, resp_rx_ts, final_tx_ts;
					uint32 poll_rx_ts_32, resp_tx_ts_32, final_rx_ts_32;
					double Ra, Rb, Da, Db;
					int64 tof_dtu;
					respTxTs = getTxTimeStampU64();//获取发送响应时间
					finalRxTs = getRxTimeStampU64();//获取最后接收时间					
					finalMsgGetTs(&rxBuffer[FINAL_MSG_POLL_TX_TS_IDX], &poll_tx_ts);//获取最后时间戳
					finalMsgGetTs(&rxBuffer[FINAL_MSG_RESP_RX_TS_IDX], &resp_rx_ts);
					finalMsgGetTs(&rxBuffer[FINAL_MSG_FINAL_TX_TS_IDX], &final_tx_ts);			
					poll_rx_ts_32 = (uint32)pollRxTs;//计算飞行时间
					resp_tx_ts_32 = (uint32)respTxTs;
					final_rx_ts_32 = (uint32)finalRxTs;
					Ra = (double)(resp_rx_ts - poll_tx_ts); 
					Rb = (double)(final_rx_ts_32 - resp_tx_ts_32);
					Da = (double)(final_tx_ts - resp_rx_ts);
					Db = (double)(resp_tx_ts_32 - poll_rx_ts_32);
					tof_dtu = (int64)((Ra * Rb - Da * Db) / (Ra + Rb + Da + Db));					
					tof = tof_dtu * DWT_TIME_UNITS;
					*dis = tof * SPEED_OF_LIGHT;					
                }										
			}
			else dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_ALL_RX_ERR);//否则清除RX错误事件	          		
		}
    }
	else dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_ALL_RX_ERR);//否则清除RX错误事件		
}
