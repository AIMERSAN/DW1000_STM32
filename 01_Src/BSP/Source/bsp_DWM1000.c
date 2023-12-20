/**
  ******************************************************************************
  * @file    bsp_DWM1000.c
  * @author  YH
  * @version V1.0
  * @date    2023 
  * @brief   
  ******************************************************************************
  * @attention
  ******************************************************************* ***********
  */

#include <stdint.h>

#include "bsp_DWM1000.h"

#include "stm32f10x.h"

#include "drv_Spi.h"
#include "drv_Gpio.h"
#include "drv_Mcu.h"

#include "deca_spi.h"
#include "deca_sleep.h"
#include "deca_device_api.h"

extern __IO unsigned long time32Incr;

spiHandleConfig_t spiHandleConfig;

void Dwm1000SpiInit(void)
{
    /* 初始化SPI4个引脚 */
    SpiGpioInit(DWM1000_SPI_CS_PORT, DWM1000_SPI_CS_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
    SpiGpioInit(DWM1000_SPI_MOSI_PORT, DWM1000_SPI_MOSI_PIN, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
    SpiGpioInit(DWM1000_SPI_MISO_PORT, DWM1000_SPI_MISO_PIN, GPIO_Mode_IPU, GPIO_Speed_50MHz);
    SpiGpioInit(DWM1000_SPI_CLK_PORT, DWM1000_SPI_CLK_PIN, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);

    GpioWriteToOutputPin(DWM1000_SPI_CS_PORT, DWM1000_SPI_CS_PIN, SET);

    SPI_I2S_DeInit(DWM1000_SPI);

    spiHandleConfig.pSPIx = DWM1000_SPI;
    spiHandleConfig.spiParamConfig.spiBaudRatePrescaler = SPI_BaudRatePrescaler_8;
    spiHandleConfig.spiParamConfig.spiCPHA = SPI_CPHA_1Edge;
    spiHandleConfig.spiParamConfig.spiCPOL = SPI_CPOL_Low;
    spiHandleConfig.spiParamConfig.spiCRCPolynomialValue = 7;
    spiHandleConfig.spiParamConfig.spiDataDirection = SPI_Direction_2Lines_FullDuplex; 
    spiHandleConfig.spiParamConfig.spiDataSize = SPI_DataSize_8b;
    spiHandleConfig.spiParamConfig.spiLSB_MSB =  SPI_FirstBit_MSB;
    spiHandleConfig.spiParamConfig.spiMode = SPI_Mode_Master;
    spiHandleConfig.spiParamConfig.spiNSS =  SPI_NSS_Soft;
    SpiParamInit(&spiHandleConfig);

    SpiPeripheralClockConfig(spiHandleConfig.pSPIx, ENABLE);

    /* 初始化先配置拉高CS引脚 */
    GpioWriteToOutputPin(DWM1000_SPI_CS_PORT, DWM1000_SPI_CS_PIN, SET);
}

void Dwm1000Reset(void)
{
    /* init the DWM1000_RST_PIN */
    SpiGpioInit(DWM1000_RST_PORT, DWM1000_RST_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

    /* drive the DWM1000_RST_PIN in low*/
    GpioWriteToOutputPin(DWM1000_RST_PORT, DWM1000_RST_PIN, RESET);

    SpiGpioInit(DWM1000_RST_PORT, DWM1000_RST_PIN, GPIO_Mode_AIN, GPIO_Speed_50MHz);


}

void Dwm1000RSTnIrqConfig(int enable)
{
    EXTI_InitTypeDef extiInitStructure;
    NVIC_InitTypeDef nvicInitSturucture;
    gpioHandle_t     gpioConfigHandle;
    
    if(enable)    
    {
        gpioConfigHandle.pGPIOx = DWM1000_RSTIRQ_EXTI_PORT;
        gpioConfigHandle.gpioPinConfig.gpioPin = DWM1000_RSTIRQ_EXTI_PIN;
        gpioConfigHandle.gpioPinConfig.gpioPortMode = GPIO_Mode_IN_FLOATING;
        gpioConfigHandle.gpioPinConfig.gpioPortSpeed = GPIO_Speed_50MHz;
        GpioConfigInit(DWM1000_IRQ_EXTI_PORT, &gpioConfigHandle);
        GPIO_EXTILineConfig(DWM1000_RSTIRQ_EXTI_PORT, DWM1000_RSTIRQ_EXTI_PIN);

        extiInitStructure.EXTI_Line = DWM1000_RSTIRQ_EXTI;
        extiInitStructure.EXTI_LineCmd = ENABLE;
        extiInitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        extiInitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_Init(&extiInitStructure);

        /* Set NVIC Grouping to 16 groups of interrupt without sub-grouping */
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

        nvicInitSturucture.NVIC_IRQChannel = DWM1000_IRQ_EXTI_IRQn;
        nvicInitSturucture.NVIC_IRQChannelCmd = ENABLE;
        nvicInitSturucture.NVIC_IRQChannelPreemptionPriority =  15;
        nvicInitSturucture.NVIC_IRQChannelSubPriority = 0;
        NVIC_Init(&nvicInitSturucture);
    }
    else
    {   
        gpioConfigHandle.gpioPinConfig.gpioPin = DWM1000_RST_PIN;
        gpioConfigHandle.gpioPinConfig.gpioPortMode = GPIO_Mode_AIN;
        gpioConfigHandle.gpioPinConfig.gpioPortSpeed = GPIO_Speed_50MHz;
        GpioConfigInit(DWM1000_RST_PORT, &gpioConfigHandle);

        extiInitStructure.EXTI_Line = DWM1000_RSTIRQ_EXTI;
        extiInitStructure.EXTI_LineCmd = ENABLE;
        extiInitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        extiInitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_Init(&extiInitStructure);
    }
}

void Dwm1000SetBaudRate(uint16_t scalingFactor)
{
    spiHandleConfig.spiParamConfig.spiBaudRatePrescaler = scalingFactor;
    
    SpiParamInit(&spiHandleConfig);

    /* 直接写寄存器写法 */
    // uint16_t tmpReg = 0;
    
    // tmpReg = spiHandleConfig.pSPIx->CR1;
    // tmpReg &= 0xFFC7;
    // tmpReg |= scalingFactor;
    // spiHandleConfig.pSPIx->CR1 = tmpReg; 
}

unsigned long getTickCount(void)
{
	return time32Incr;
}
