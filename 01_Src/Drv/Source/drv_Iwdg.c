/**
  ******************************************************************************
  * @author  
  * @date    
  * @brief   配置8266
  ******************************************************************************
	一,使用说明:
		1,初始化喂狗
			IWDG_Init(uint8_t prescaleVal, uint16_t reloadVal); 
		
		2,调用使用
			IWDG_Feed();//喂狗
  ******************************************************************************
  */

#define IWDG_C_
#include "drv_iwdg.h"

/**
  * @brief  独立看门狗初始化
  * @param  uint8_t prescaleVal：预分频值，0~7，低3位有效
  * @param  uint16_t reloadVal ：重装载值，0~4096，低11位有效
  * @retval None
  * @note
  * 喂狗时间计算 Tout = ((4 * 2 ^ prescaleVal) * reloadVal) / 40 (ms)
  */
void IWDG_Init(uint8_t prescaleVal, uint16_t reloadVal) 
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
    
    IWDG_SetPrescaler(prescaleVal);  //设置IWDG预分频值:设置IWDG预分频值为64
    
    IWDG_SetReload(reloadVal);  //设置IWDG重装载值
    
    IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
    
    IWDG_Enable();  //使能IWDG
}

/**
  * @brief  独立看门狗喂狗
  * @param  None
  * @retval None
  * @note
  */
void IWDG_Feed(void)
{
    IWDG_ReloadCounter();
}

