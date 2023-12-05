/**
  ******************************************************************************
  * @file    drv_Rcc.c
  * @author  YH
  * @version V1.0
  * @date    2023 
  * @brief   RCC Driver Source File
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
  
#include "drv_Rcc.h"

void RccInit()
{
    setAHB1lock();
    
    

}

void SetAHB1lock(RCC_Handle_t* pRCCHandle){
    uint8_t i = 0;
    uint32_t temp = 0;
    uint8_t  value = 0;
    
    if(pRCCHandle->RCC_Config.AHB_ClockFreq <= )

}

void SetAPB1Clock()
{


}

void SetAPB2Clock()
{


}

void ChangeClockSource()
{


}

uint16_t GetClockSource()
{


}

uint32_t GetAHBClock()
{


}

uint32_t GetAPB1Clock()
{


}

uint32_t GetAPB2Clock()
{


}





