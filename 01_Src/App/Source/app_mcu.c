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

void Init(void)
{   
    
}

void DeviceInit(void)
{
    Dwm1000SpiInit();
    Dwm1000DeviceInit();
    LedGpioInit();
    BeeGpioInit();
}
