#ifndef __BSP_LED_H_
#define __BSP_LED_H_




#define LED_PORT GPIOA
#define LED_PIN  GPIO_Pin_0 

void LedGpioInit();
void LedOn(void);
void LedOff(void);
void LedToggle(void);

#endif
