/**
  ******************************************************************************
  * @file    app_mcu.c
  * @author  YH
  * @version V1.0
  * @date    2023
  * @brief   设备应用源文件
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "app_mcu.h"
#include "app_dwm1000.h"

#include "bsp_DWM1000.h"
#include "bsp_Bee.h"
#include "bsp_Led.h"

#include "drv_Uart.h"
#include "drv_Timer.h"
#include "drv_Mcu.h"

void BspInit(void)
{   
    SysTickDelayInit();
    SysTickHandlerConfig();
    Uart_Init(9600);
}

void DeviceInit(void)
{
    Dwm1000DeviceInit();
    LedGpioInit();
    BeeGpioInit();
}
