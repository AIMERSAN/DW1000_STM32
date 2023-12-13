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

void BeeInitConfig(void)
{
    gpioHandle_t beeGpioHandle;
    
    beeGpioHandle.pGPIOx = A1_GPIO_PORT;
    beeGpioHandle.gpioPinConfig.gpioPin = A1_GPIO_PIN | A2_GPIO_PIN;
    beeGpioHandle.gpioPinConfig.gpioPortMode = GPIO_Mode_Out_PP;
    beeGpioHandle.gpioPinConfig.gpioPortSpeed = GPIO_Speed_50MHz;

    GPIO_DeInit(beeGpioHandle.pGPIOx);
    GpioPeripheralClockConfig(beeGpioHandle.pGPIOx, ENABLE);
    GpioConfigInit(beeGpioHandle.pGPIOx, &beeGpioHandle);
}

void BeeClose(void)
{
    GpioWriteToOutputPin(A1_GPIO_PORT, A1_GPIO_PIN, RESET);
}

void BeeOpen(void)
{
    GpioWriteToOutputPin(A1_GPIO_PORT, A1_GPIO_PIN, SET);
}
