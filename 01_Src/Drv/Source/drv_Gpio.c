/**
  ******************************************************************************
  * @file    drv_Gpio.c
  * @author  YH
  * @version V1.0
  * @date    2023 
  * @brief   GPIO Driver Source File
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "drv_Gpio.h"


void GpioPeripheralClockConfig(GPIO_TypeDef *pGPIOx, FunctionalState clockState)
{

    switch((uint16_t)pGPIOx)
    {
        case GPIOA:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, clockState);
            break;
        case GPIOB:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, clockState);
            break;
        case GPIOC:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, clockState);
            break;
        case GPIOD:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, clockState);
            break;
        case GPIOE:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, clockState);
            break;
        case GPIOF:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, clockState);
            break;
        case GPIOG:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, clockState);
            break;
        default:
            break;
    }
}

void GpioConfig(GPIO_TypeDef* pGPIOx, gpioHandle_t* pGpioHandle)
{
    GPIO_InitTypeDef gpioInitstructure;

    gpioInitstructure.GPIO_Mode = pGpioHandle->gpioPinConfig.gpioPortMode;
    gpioInitstructure.GPIO_Speed = pGpioHandle->gpioPinConfig.gpioPortSpeed;
    gpioInitstructure.GPIO_Pin = pGpioHandle->gpioPinConfig.gpioPin;

    GPIO_Init(pGPIOx, &gpioInitstructure);
}

/* 后续添加中断处理功能 */


