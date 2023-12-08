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
#include "stm32f10x_spi.h"

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

/* SPI Parameter Config Struct define */
typedef struct 
{
    uint16_t spiBaudRatePrescaler;
    uint16_t spiCPOL;
    uint16_t spiCPHA;
    uint16_t spiCRCPolynomialValue;
    uint16_t spiDataSize;
    uint16_t spiDataDirection;
    uint16_t spiLSB_MSB;
    uint16_t spiMode;
    uint16_t spiNSS;
}spiParamConfig_t;

/* SPI Parameter Config Struct define */
typedef struct
{
    /* data */
    SPI_TypeDef *pSPIx;
    spiParamConfig_t spiParamConfig;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint32_t txLen;
    uint32_t rxLen;
    uint8_t  txState; 
}spiHandleConfig_t;

#endif
