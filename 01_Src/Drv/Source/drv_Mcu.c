



#include "drv_Mcu.h"
#include <stdlib.h>
#include <stdio.h>

static uint8_t  fac_us=0;
static uint16_t fac_ms=0;

uint32_t idAddr[]= {
    0x1FFFF7AC,/*STM32F0唯一ID起始地址*/
    0x1FFFF7E8,/*STM32F1唯一ID起始地址*/
    0x1FFF7A10,/*STM32F2唯一ID起始地址*/
    0x1FFFF7AC,/*STM32F3唯一ID起始地址*/
    0x1FFF7A10,/*STM32F4唯一ID起始地址*/
    0x1FF0F420,/*STM32F7唯一ID起始地址*/
    0x1FF80050,/*STM32L0唯一ID起始地址*/
    0x1FF80050,/*STM32L1唯一ID起始地址*/
    0x1FFF7590,/*STM32L4唯一ID起始地址*/
    0x1FF0F420 /*STM32H7唯一ID起始地址*/
};

void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
}

/*复位芯片*/
void Reset_MCU(void)
{
    __disable_fault_irq();
    NVIC_SystemReset();
}

/*获取MCU唯一ID*/
void GetSTM32MCUID(uint32_t *MCUID,char AddrID)
{
    if(MCUID!=NULL)
    {
        MCUID[0]=*(uint32_t*)(idAddr[AddrID]);
        MCUID[1]=*(uint32_t*)(idAddr[AddrID]+4);
        MCUID[2]=*(uint32_t*)(idAddr[AddrID]+8);

        printf("\r\n 芯片唯一ID: %X-%X-%X\r\n",MCUID[0],MCUID[1],MCUID[2]);
    }
}

/**
  * @brief  系统滴答定时器延时初始化
  * @param  None
  * @retval None
  */
void Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us=SystemCoreClock/8000000;
    fac_ms=(u16)fac_us*1000;
}


/**
  * @brief  MCU微妙级延时
  * @param  uint32_t nus
  * @retval None
  */
void delay_us(uint32_t nus)
{
    u32 temp;
    SysTick->LOAD=nus*fac_us;
    SysTick->VAL=0x00;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
    do
    {
        temp=SysTick->CTRL;
    } while((temp&0x01)&&!(temp&(1<<16)));
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL =0X00;
}

/**
  * @brief  MCU毫秒级延时
  * @param  uint32_t nms
  * @retval None
  */
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD=(u32)nms*fac_ms;
    SysTick->VAL =0x00;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
    do
    {
        temp=SysTick->CTRL;
    } while((temp&0x01)&&!(temp&(1<<16)));
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL =0X00;
}


