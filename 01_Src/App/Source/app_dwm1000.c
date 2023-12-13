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

#include "app_dwm1000.h"


void Dwm1000DeviceInit(void)
{   
    Dwm1000SpiInit();
    
    deca_sleep(10);

    Dwm1000Reset();

    /* 睡眠延时 */
    deca_sleep(2);

    Dwm1000SetBaudRate(DWM1000_LOWSPIBaudRate);

    while();

    Dwm1000SetBaudRate(DWM1000_HIGHSPIBaudRate);

}

