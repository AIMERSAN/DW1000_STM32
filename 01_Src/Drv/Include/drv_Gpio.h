/**
  ******************************************************************************
  * @file    drv_Gpio.h
  * @author  YH
  * @version V1.0
  * @date    2023 
  * @brief   Gpio Driver Head File
  ******************************************************************************
  * @attention
  ******************************************************************************
  */


#ifndef __DRV_GPIO_H_
#define __DRV_GPIO_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

typedef struct 
{
    /* data */
    uint16_t gpioPin;
    uint16_t gpioPortMode;
    uint16_t gpioPortSpeed;
    
    
}gpioPinConfig_t;

typedef struct
{
    GPIO_TypeDef *pGPIOx; 
    gpioPinConfig_t gpioPinConfig; 
}gpioHandle_t;

    




#endif