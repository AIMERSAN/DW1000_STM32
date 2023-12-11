/**
  ******************************************************************************
  * @file    bsp_Bee.c
  * @author  YH
  * @version V1.0
  * @date    2023 
  * @brief   蜂鸣器板级驱动文件
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "bsp_Bee.h"

gpioHandle_t gpioHandle;

void BeeInit()
{
    gpioHandle.pGPIOx = A1_GPIO_PORT | A2_GPIO_PORT;
    gpioHandle.gpioPinConfig.gpioPin = A1_GPIO_PIN | A2_GPIO_PIN;
    gpioHandle.gpioPinConfig.gpioPortMode = GPIO_Mode_Out_PP;
    gpioHandle.gpioPinConfig.gpioPortSpeed = GPIO_Speed_50MHz;
    
    GpioPeripheralClockConfig(gpioHandle.pGPIOx, ENABLE);    
    GpioConfigInit(gpioHandle.pGPIOx, &gpioHandle);
}

void BeeClose()
{
    

}

void BeeOpen()
{


}

