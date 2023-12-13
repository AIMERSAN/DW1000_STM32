/**
  ******************************************************************************
  * @file    drv_Spi.c
  * @author  YH
  * @version V1.0
  * @date    2023 
  * @brief   SPI Driver Source File
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "drv_Spi.h"
#include "drv_gpio.h"

void SpiPeripheralClockConfig(SPI_TypeDef *pSPIx, FunctionalState clockState)
{
    if(pSPIx == SPI1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, clockState);
    }
    else if(pSPIx == SPI2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, clockState);
    }
    else if (pSPIx == SPI3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, clockState);
    }
}

void SpiGpioInit(GPIO_TypeDef* spiDevicePort,uint16_t spiDevicePin, 
                 uint16_t spiDevicePortMode, uint16_t spiDevicePortSpeed)
{
    gpioHandle_t spiGpioConfig;

    spiGpioConfig.pGPIOx = spiDevicePort;
    spiGpioConfig.gpioPinConfig.gpioPortMode = spiDevicePortMode;
    spiGpioConfig.gpioPinConfig.gpioPortMode  = spiDevicePin;
    spiGpioConfig.gpioPinConfig.gpioPortSpeed = spiDevicePortSpeed;
    
    GpioConfigInit(spiDevicePort, &spiGpioConfig);
}

void SpiParamInit(spiHandleConfig_t *pSpiHandle)
{
    SPI_InitTypeDef spiInitStructure;
    spiInitStructure.SPI_BaudRatePrescaler = pSpiHandle->spiParamConfig.spiBaudRatePrescaler;
    spiInitStructure.SPI_CPHA = pSpiHandle->spiParamConfig.spiCPHA;
    spiInitStructure.SPI_CPOL = pSpiHandle->spiParamConfig.spiCPOL;
    spiInitStructure.SPI_CRCPolynomial = pSpiHandle->spiParamConfig.spiCRCPolynomialValue; 
    spiInitStructure.SPI_DataSize      = pSpiHandle->spiParamConfig.spiDataSize;
    spiInitStructure.SPI_Direction     = pSpiHandle->spiParamConfig.spiDataDirection;
    spiInitStructure.SPI_FirstBit      = pSpiHandle->spiParamConfig.spiLSB_MSB;
    spiInitStructure.SPI_Mode          = pSpiHandle->spiParamConfig.spiMode;
    spiInitStructure.SPI_NSS           = pSpiHandle->spiParamConfig.spiNSS;
    
    SPI_Init(pSpiHandle->pSPIx, &spiInitStructure);
    SPI_Cmd(pSpiHandle->pSPIx, ENABLE);
}

void SpiSendData(SPI_TypeDef* pSPIx, uint8_t *pTxBuffer , uint32_t length)
{
    while(length > 0)
    {
        /* check for tx buffer empty state */
        while(SPI_I2S_GetFlagStatus(pSPIx, SPI_I2S_FLAG_TXE) == RESET){}

        /* check for data format */
        if ((pSPIx->CR1 & (1 << SPI_CR1_DFF))) 
        {
			/*16 bit data format, load 16 bit of data into DR */ 
			pSPIx->DR = *((uint16_t*)pTxBuffer) ;
			length-- ;
			length-- ;
			(uint16_t*)pTxBuffer++ ;
		} 
        else 
        {
			// load 8 bit data into DR
			pSPIx->DR = *pTxBuffer ;
			length-- ;
			pTxBuffer++ ;
		}
    }
}

void SPIReadData(SPI_TypeDef* pSPIx, uint8_t *pRxBuffer , uint32_t length)
{   
    while(length > 0)
    {
        /* check for tx buffer empty state */
        while(SPI_I2S_GetFlagStatus(pSPIx, SPI_I2S_FLAG_RXNE) == RESET){}
        
        if((pSPIx->CR1 &(1 <<SPI_CR1_DFF)))
        {
            /*16 bit data format, read 16 bit of data into DR */
            *((uint16_t*)pRxBuffer) = pSPIx->DR;
            length--;
            length--;
            (uint16_t*)pRxBuffer++;
        }        
        else
        {
            *pRxBuffer = pSPIx->DR ;
			length-- ;
			pRxBuffer++ ;
        }
    }
}
