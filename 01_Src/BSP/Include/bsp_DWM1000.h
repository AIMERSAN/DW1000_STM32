#ifndef __BSP_DWM1000_H_
#define __BSP_DWM1000_H_

#include <stdint.h>

/* DWM1000模块接口定义 */
#define DWM1000_SPI             SPI1

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

/* DWM1000 SPI接口速率定义 */
#define DWM1000_LOWSPIBaudRate  SPI_BaudRatePrescaler_32
#define DWM1000_HIGHSPIBaudRate SPI_BaudRatePrescaler_4

/* DWM1000 Reset 中断宏定义 */
#define DWM1000_RSTIRQ_PIN             GPIO_Pin_0
#define DWM1000_RSTIRQ_PORT            GPIOA
#define DWM1000_RSTIRQ_EXTI            EXTI_Line0
#define DWM1000_RSTIRQ_EXTI_PORT       GPIO_PortSourceGPIOA
#define DWM1000_RSTIRQ_EXTI_PIN        GPIO_PinSource0
#define DWM1000_RSTIRQ_EXTI_IRQn       EXTI0_IRQn

/* DWM1000 Device 中断宏定义 */
#define DWM1000_IRQ_PIN             GPIO_Pin_5
#define DWM1000_IRQ_PORT            GPIOB
#define DWM1000_IRQ_EXTI            EXTI_Line5
#define DWM1000_IRQ_EXTI_PORT       GPIO_PortSourceGPIOB
#define DWM1000_IRQ_EXTI_PIN        GPIO_PinSource5
#define DWM1000_IRQ_EXTI_IRQn       EXTI9_5_IRQn
#define DWM1000_IRQ_EXTI_USEIRQ     ENABLE
#define DWM1000_IRQ_EXTI_NOIRQ      DISABLE

#define DWM1000_GetEXT_IRQStatus() EXTIGetITEnStatus(DWM1000_IRQ_EXTI_IRQn);
#define DWM1000_DisableEXT_IRQ()   NVIC_DisableIRQ(DWM1000_IRQ_EXTI_IRQn)
#define DWM1000_EnableEXT_IRQ()    NVIC_EnableIRQ(DWM1000_IRQ_EXTI_IRQn)
#define DWM1000_CheckEXT_IRQ()     GPIO_ReadInputDataBit(DWM1000_IRQ_PORT, DWM1000_IRQ_PIN)
/* DWM1000 硬件SPI配置 */

//spiHandleConfig_t spiHandleConfig;

void Dwm1000SpiInit(void);
void Dwm1000Reset(void);
void Dwm1000RSTnIrqConfig(int enable);
uint16_t DWM1000IrqConfig(void);
void Dwm1000SetBaudRate(uint16_t scalingFactor);
unsigned long getTickCount(void);

#endif
