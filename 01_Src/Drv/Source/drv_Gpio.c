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
    if(pGPIOx == GPIOA)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, clockState);
    } 
    else if (pGPIOx == GPIOB)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, clockState);
    }
    else if (pGPIOx == GPIOC)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, clockState);
    }
    else if (pGPIOx == GPIOD)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, clockState);
    }
    else if (pGPIOx == GPIOE)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, clockState);
    }
    else if (pGPIOx == GPIOF)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, clockState);
    }
    else if (pGPIOx == GPIOG)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, clockState);
    }
}

void GpioConfigInit(GPIO_TypeDef* pGPIOx, gpioHandle_t pGpioHandle)
{
    GPIO_InitTypeDef gpioInitstructure;

    gpioInitstructure.GPIO_Mode = pGpioHandle.gpioPinConfig.gpioPortMode;
    gpioInitstructure.GPIO_Speed = pGpioHandle.gpioPinConfig.gpioPortSpeed;
    gpioInitstructure.GPIO_Pin = pGpioHandle.gpioPinConfig.gpioPin;

    GPIO_Init(pGPIOx, &gpioInitstructure);
}

void GpioWriteToOutputPin(GPIO_TypeDef* pGPIOx, uint16_t gpioPin, uint8_t pinState)
{
    if(pinState == SET)
    {
        pGPIOx->ODR = (1 << gpioPin);
    }
    else if(pinState == RESET)
    {
        pGPIOx->ODR = ~(1 << gpioPin);
    }
}

void GpioWriteToOutputPort(GPIO_TypeDef* pGPIOx, uint8_t portStateValue)
{
    pGPIOx->ODR = portStateValue;
}

void GpioToggleOutputPin(GPIO_TypeDef* pGPIOx, uint16_t gpioPin)
{
    pGPIOx->ODR = pGPIOx->ODR ^ (1 << gpioPin);
}

/* 后续添加中断处理功能 */
