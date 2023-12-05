/**
  ******************************************************************************
  * @file    drv_Spi.h
  * @author  YH
  * @version V1.0
  * @date    2023 
  * @brief   SPI Driver Head File
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
  
#ifndef __DRV_SPI_H_
#define __DRV_SPI_H_

#include "stm32f10x.h"

/* DWM1000模块接口定义 */
#define DWM1000_SPI            SPI1

#define DWM1000_SPI_CS_PORT     GPIOA
#define DWM1000_SPI_CS_PIN      GPIO_Pin_4

#define DWM1000_SPI_CLK_PORT    GPIOA
#define DWM1000_SPI_CLK_PIN     GPIO_Pin_5

#define DWM1000_SPI_MISO_PORT   GPIOA
#define DWM1000_SPI_MISO_PIN    GPIO_Pin_6

#define DWM1000_SPI_MOSI_PORT   GPIOA
#define DWM1000_SPI_MOSI_PIN    GPIO_Pin_7

#define DWM1000_RST_PORT        GPIOA
#define DWM1000_RST_PIN         GPIO_Pin_0



#endif
