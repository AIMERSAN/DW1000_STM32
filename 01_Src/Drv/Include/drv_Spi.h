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

void SpiPeripheralClockConfig(SPI_TypeDef *pSPIx, FunctionalState clockState);
void SpiGpioInit(GPIO_TypeDef* spiDevicePort, uint16_t spiDevicePortMode, 
                    uint16_t spiDevicePin, uint16_t spiDevicePortSpeed);
void SpiParamInit(spiHandleConfig_t *pSpiHandle);
void SpiSendData(SPI_TypeDef* pSPIx, uint8_t *pTxBuffer , uint32_t length);
void SPIReadData(SPI_TypeDef* pSPIx, uint8_t *pRxBuffer , uint32_t length);
    

#endif
