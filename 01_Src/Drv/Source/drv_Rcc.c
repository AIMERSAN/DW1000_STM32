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
    setAHB1lock(pRCCHanle);
    
    

}

/**
  * @brief  设置AHB时钟
  * @param  RCC_Handle_t* pRCCHandle
  * @retval None
  */
void SetAHBlock(RCC_Handle_t* pRCCHandle)
{
    uint8_t  i = 0;
    uint32_t temp = 0;
    uint8_t  preValueOfAHB = 0;
    
    if((pRCCHandle->RCC_Config.AHB_ClockFreq <= SYSTEM_HSI) || 
        (pRCCHandle->RCC_Config.AHB_ClockFreq <= SYSTEM_HSE))
    {
        if(pRCCHandle->RCC_Config.clockSource == HSI_CLOCK)
        {
            i = 0;
            temp = SYSTEM_HSI / pRCCHandle->RCC_Config.AHB_ClockFreq;
            preValueOfAHB = 0;
            if(temp == 1)
            {
                preValueOfAHB = 0;
            }
            if (temp >= 64) 
            {
                temp = temp / 2 ;
            }
            if(temp >= 2)
            {
                preValueOfAHB = 8;
                for( ;temp != 2; i++)
                {
                    temp = temp / 2;
                }
                preValueOfAHB = preValueOfAHB + i;
            #if RCC_DEBUG
                    printf(printf("Clock selected HSI stock at : %d running at : %d\n " , SYSTEM_HSI , pRCCHandle->RCC_Config.AHB_ClockFreq); )
                    printf("AHB HPRE value %d\n " , value);
            #endif
            }
            pRCCHandle->pRCC->CFGR &= ~( 0x0F << 4 );
            pRCCHandle->pRCC->CFGR |= ( preValueOfAHB << 4 );
            i = 0;
            preValueOfAHB = 0;
        }
        else if(pRCCHandle->RCC_Config.clockSource == HSE_CLOCK)
        {
            i = 0;
            temp = SYSTEM_HSE / pRCCHandle->RCC_Config.AHB_ClockFreq;
            preValueOfAHB = 0;
            if(temp == 1)
            {
                preValueOfAHB = 0;
            }
            if (temp >= 64) 
            {
                temp = temp / 2 ;
            }
            if(temp >= 2)
            {
                preValueOfAHB = 8;
                for( ;temp != 2; i++)
                {
                    temp = temp / 2;
                }
                preValueOfAHB = preValueOfAHB + i;
            #if RCC_DEBUG
                    printf(printf("Clock selected HSI stock at : %d running at : %d\n " , SYSTEM_HSI , pRCCHandle->RCC_Config.AHB_ClockFreq); )
                    printf("AHB HPRE value %d\n " , value);
            #endif
            }
            pRCCHandle->pRCC->CFGR &= ~( 0x0F << 4 );
            pRCCHandle->pRCC->CFGR |= ( preValueOfAHB << 4 );
            i = 0;
            preValueOfAHB = 0;
        }
        else if(pRCCHandle->RCC_Config.clockSource == PLL_CLOCK)
        {
            if(GetClockSource(pRCCHandle) == PLL_CLOCK)
            {
                /* PLL cannot be configured when PLL is ON, switch the clock to HSI */
                pRCCHandle->RCC_Config.clockSource = HSI_CLOCK ;
                changeClockSource(pRCCHandle) ;
                /* turn off PLL */ 
                pRCCHandle->pRCC->CR &= ~(1 << RCC_CR_PLLON) ;
                pRCCHandle->RCC_Config.clockSource = PLL_CLOCK ;
            }
            
            /* Configure the PLL engine, max SYSCLK that can be achieved is 72MHZ */
            if(pRCCHandle->RCC_Config.PLLSource == HSI_CLOCK / 2)
            {
                pRCCHandle->pRCC->CR |= (1 << RCC_CR_HSION);
                while(!(pRCCHandle->pRCC->CR &(1 << RCC_CR_HSIRDY)));
                
                /*load value in PLLMUL, can be 2~16*/
                
                /*clean PLLMUL PLLXTPRE PLLSRC bit of CFGR*/
                pRCCHandle->pRCC->CFGR &= (uint32_t)(~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
                
                pRCCHandle->pRCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_Div2 | RCC_CFGR_PLLMULL2);
                
                /* // load value 8 in M
                pRCCHandle->pRCC->PLLCFGR &= ~(0x3F << 0) ;		// clearing the proper bit field bug fix
                pRCCHandle->pRCC->PLLCFGR |= (0x08 << 0) ;
                // load the frequency value in N
                pRCCHandle->pRCC->PLLCFGR &= ~((0x1FF) << 6) ;
                pRCCHandle->pRCC->PLLCFGR |= ((pRCCHandle->RCC_Config.AHB_ClockFreq / 1000000) << 6) ;

                // load the value in P
                pRCCHandle->pRCC->PLLCFGR &= ~(0x03 << 16) ;
                */

            }
            else if (pRCCHandle->RCC_Config.PLLSource == HSE_CLOCK) 
            {
                /*enable the HSE */ 
                pRCCHandle->pRCC->CR |= (1 << RCC_CR_HSEON) ;
                while(!(pRCCHandle->pRCC->CR & (1 << RCC_CR_HSERDY) )) ;
                
                /*load value in PLLMUL, can be 2~16*/
                
                /*clean PLLMUL PLLXTPRE PLLSRC bit of CFGR*/
                pRCCHandle->pRCC->CFGR &= (uint32_t)(~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
                
                pRCCHandle->pRCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL2);
                
                /*
                // load value 4 in M
                pRCCHandle->pRCC->PLLCFGR &= ~(0x3F<< 0) ;
                pRCCHandle->pRCC->PLLCFGR |= (0x04 << 0) ;
                // load the frequency value in N
                pRCCHandle->pRCC->PLLCFGR &= ~((0x1FF) << 6) ;
                pRCCHandle->pRCC->PLLCFGR |= ((pRCCHandle->RCC_Config.AHB_ClockFreq / 1000000) << 6) ;
                // load the value in P
                pRCCHandle->pRCC->PLLCFGR &= ~(0x03 << 16) ;
                */
            }
            
            FLASH->ACR = FLASH_ACR_PRFTBE;
            FLASH->ACR &= (uint32_t)((uint32_t) ~FLASH_ACR_LATENCY);
            
            if(pRCCHandle->RCC_Config.AHB_ClockFreq > 48000000 && pRCCHandle->RCC_Config.AHB_ClockFreq < 72000000)
            {
                FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;
            }
        }
    }
}

/**
  * @brief  配置APB1的时钟
  * @param  RCC_Handle_t* pRCCHandle
  * @retval 对应时钟源大小
  */
void SetAPB1Clock(RCC_Handle_t* pRCCHandle)
{   
    uint32_t temp = 1 ;
    uint32_t value = 0 ;
    uint32_t i = 0 ;
    
    if(((pRCCHandle->RCC_Config.clockSource == HSI_CLOCK) ||
        (pRCCHandle->RCC_Config.clockSource == HSE_CLOCK)) &&
        (pRCCHandle->RCC_Config.APB1_ClockFreq <= SYSTEM_HSI)) 
    {
        if(GetAHBClock(pRCCHandle) < pRCCHandle->RCC_Config.APB1_ClockFreq)
        {
        #if RCC_DEBUG
            printf("ERR : APB1 FREQ : %d not possible AHB1 is : %d\n " , pRCCHandle->RCC_Config.APB1_ClockFreq , getAHBClock(pRCCHandle)) ;
        #endif
        return ;
        }
        temp = getAHBClock(pRCCHandle) / pRCCHandle->RCC_Config.APB1_ClockFreq ;
        if(temp == 1)
        {
            value = 0 ;
        }
        if (temp >= 2)
        {
            value =  4;
            for ( ;temp !=2 ; i++)
            {
                temp = temp / 2 ;
            }
            value = value + i ;
         #if RCC_DEBUG
            printf("APB1 PRE1 value %d\n " , value ) ;
         #endif
        }
        pRCCHandle->pRCC->CFGR &= ~( 0x07 << 10 ) ;
        pRCCHandle->pRCC->CFGR |= ( value << 10 ) ;
        i = 0 ;
        value = 0 ;
    }
    else if(pRCCHandle->RCC_Config.clockSource == PLL_CLOCK)
    {
        temp = getAHBClock(pRCCHandle) ;
        i = 1 ;
        if (pRCCHandle->RCC_Config.APB1_ClockFreq > APB1_MAX_FREQ)
        {
        #if RCC_DEBUG
            printf("APB1 Freq : %d not possible setting it to max possible \n" , pRCCHandle->RCC_Config.APB1_ClockFreq) ;
        #endif
            pRCCHandle->RCC_Config.APB1_ClockFreq = APB1_MAX_FREQ ;
        }

        while(1)
        {
            if(temp <= pRCCHandle->RCC_Config.APB1_ClockFreq)
            {
                // check to see if its under limit the APB1 can handle
                if (temp <= APB1_MAX_FREQ) 
                {
                    // capture the value of temp and break the loop
                    break ;
                }
            }
            temp = temp / 2 ;
            i = i * 2 ;
        }
        #if RCC_DEBUG
            printf("APB1 PRE1 value %d\n " , value ) ;
        #endif

        if (i == 1)
        {
            value =  0 ;
        }
        else if (i == 2)
        {
            value = 4 ;
        }
        else if (i == 4)
        {
            value = 5 ;
        }else if(i == 8)
        {
            value = 6 ;
        }
        else if (i == 16)
        {
            value = 7 ;
        }
        pRCCHandle->pRCC->CFGR &= ~( 0x07 << 10 ) ;
        pRCCHandle->pRCC->CFGR |= ( value << 10 ) ;
    }

}

void SetAPB2Clock(RCC_Handle_t* pRCCHandle)
{
    uint32_t temp = 1 ;
    uint32_t value = 0 ;
    uint32_t i = 0 ;
    
    if(((pRCCHandle->RCC_Config.clockSource == HSI_CLOCK) ||
        (pRCCHandle->RCC_Config.clockSource == HSE_CLOCK)) &&
        (pRCCHandle->RCC_Config.APB1_ClockFreq <= SYSTEM_HSI)) 
    {
        if(GetAHBClock(pRCCHandle) < pRCCHandle->RCC_Config.APB2_ClockFreq)
        {
        #if RCC_DEBUG
            printf("ERR : APB2 FREQ : %d not possible AHB1 is : %d\n " , pRCCHandle->RCC_Config.APB2_ClockFreq , GetAHBClock(pRCCHandle)) ;
        #endif
        return ;
        }
        temp = getAHBClock(pRCCHandle) / pRCCHandle->RCC_Config.APB2_ClockFreq ;
        if(temp == 1)
        {
            value = 0 ;
        }
        if (temp >= 2)
        {
            value =  4;
            for ( ;temp !=2 ; i++)
            {
                temp = temp / 2 ;
            }
            value = value + i ;
         #if RCC_DEBUG
            printf("APB1 PRE1 value %d\n " , value ) ;
         #endif
        }
        pRCCHandle->pRCC->CFGR &= ~( 0x07 << 10 ) ;
        pRCCHandle->pRCC->CFGR |= ( value << 10 ) ;
        i = 0 ;
        value = 0 ;
    }
    else if(pRCCHandle->RCC_Config.clockSource == PLL_CLOCK)
    {
        temp = getAHBClock(pRCCHandle) ;
        i = 1 ;
        if (pRCCHandle->RCC_Config.APB2_ClockFreq > APB2_MAX_FREQ)
        {
        #if RCC_DEBUG
            printf("APB1 Freq : %d not possible setting it to max possible \n" , pRCCHandle->RCC_Config.APB1_ClockFreq) ;
        #endif
            pRCCHandle->RCC_Config.APB2_ClockFreq = APB2_MAX_FREQ ;
        }

        while(1)
        {
            if(temp <= pRCCHandle->RCC_Config.APB2_ClockFreq)
            {
                // check to see if its under limit the APB1 can handle
                if (temp <= APB2_MAX_FREQ) 
                {
                    // capture the value of temp and break the loop
                    break ;
                }
            }
            temp = temp / 2 ;
            i = i * 2 ;
        }
        #if RCC_DEBUG
            printf("APB2 PRE1 value %d\n " , value ) ;
        #endif

        if (i == 1)
        {
            value =  0 ;
        }
        else if (i == 2)
        {
            value = 4 ;
        }
        else if (i == 4)
        {
            value = 5 ;
        }else if(i == 8)
        {
            value = 6 ;
        }
        else if (i == 16)
        {
            value = 7 ;
        }
        /* 需要修改适配stm32f103*/
        pRCCHandle->pRCC->CFGR &= ~( 0x07 << 13 ) ;
        pRCCHandle->pRCC->CFGR |= ( value << 13 ) ;
    }

}

/**
  * @brief  获取当前时钟源
  * @param  RCC_Handle_t* pRCCHandle
  * @retval 对应时钟源大小
  */
uint16_t GetClockSource(RCC_Handle_t* pRCCHandle)
{
    if ((pRCCHandle->pRCC->CFGR & 0x0C ) == 0x00) 
    {
#if RCC_DEBUG
        printf("CLOCK source HSI: %d \n" ,(pRCCHandle->pRCC->CFGR & 0x0C ) >> 0) ;
#endif
        return HSI_CLOCK ;
    }
    else if ((pRCCHandle->pRCC->CFGR & 0x0C ) == 0x04)
    {
#if RCC_DEBUG
        printf("CLOCK source HSE: %d \n" ,(pRCCHandle->pRCC->CFGR & 0x0C ) >> 0) ;
#endif
        return HSE_CLOCK ;
    }
    else if ((pRCCHandle->pRCC->CFGR & 0x0C ) == 0x08)
    {
#if RCC_DEBUG
        printf("CLOCK source PLL: %d \n" ,(pRCCHandle->pRCC->CFGR & 0x0C ) >> 0) ;
#endif
        return PLL_CLOCK ;
    }
    
    return 0;
}

/**
  * @brief  改变当前时钟源
  * @param  RCC_Handle_t* pRCCHandle
  * @retval None
  */
void ChangeClockSource(RCC_Handle_t* pRCCHandle) 
{

    if (pRCCHandle->RCC_Config.clockSource == HSI_CLOCK) 
    {
        pRCCHandle->pRCC->CR |= (1 << RCC_CR_HSION) ;
        while(!(pRCCHandle->pRCC->CR & (1 << RCC_CR_HSIRDY)));
        pRCCHandle->pRCC->CFGR &= ~(3 << 0) ;
    }
    else if(pRCCHandle->RCC_Config.clockSource == HSE_CLOCK)
    {
        pRCCHandle->pRCC->CR |= (1 << RCC_CR_HSEON) ;
        while(!(pRCCHandle->pRCC->CR & (1 << RCC_CR_HSERDY)));
        pRCCHandle->pRCC->CFGR |= (1 << 0) ;
    }
    else if(pRCCHandle->RCC_Config.clockSource == PLL_CLOCK)
    {
        pRCCHandle->pRCC->CR |= (1 << RCC_CR_PLLON) ;
        while(!(pRCCHandle->pRCC->CR & (1 << RCC_CR_PLLRDY)));
        pRCCHandle->pRCC->CFGR |= (1 << 1) ;
    }
}

/**
  * @brief  获取当前AHB时钟值
  * @param  RCC_Handle_t* pRCCHandle
  * @retval None
  */
uint32_t GetAHBClock(RCC_Handle_t* pRCCHandle)
{
    uint32_t tempValueOfHRRE = 0 ;
    
    /* AHB Prescaler's value */
    uint32_t valueOfAHBPre = 2 ;
    
    uint32_t tempValueOfPLLCLK;
    
    if (pRCCHandle->RCC_Config.clockSource == HSI_CLOCK)
    {
        /* default for HSI is 8MHZ */

        /* get the value RCC_CFGR's HPRE bit, then shift four bit to the right, convert to ... */
        tempValueOfHRRE = ((pRCCHandle->pRCC->CFGR & 0xF0 ) >> 4);
        if(tempValueOfHRRE >= 12)
        {
            valueOfAHBPre = 4 ;		// 8, 16, 32, 64, 128, 256
        }
        if(tempValueOfHRRE > 8)
        {
            tempValueOfHRRE = tempValueOfHRRE - 8 ;
            for (uint8_t i = 0;  i < tempValueOfHRRE; i++)
            {
                /* for every loop we double the value of 2 */ 
                valueOfAHBPre = valueOfAHBPre * 2;
            }
         }
        else if (tempValueOfHRRE == 8)
        {
            valueOfAHBPre = 2 ;
        }
        else
        {
            valueOfAHBPre = 1 ;
        }
        return (SYSTEM_HSI / valueOfAHBPre) ;
    }
    else if (pRCCHandle->RCC_Config.clockSource == HSE_CLOCK)
    {
        /* default for HSE is 8MHZ */
        tempValueOfHRRE = ((pRCCHandle->pRCC->CFGR & 0xF0 ) >> 4);
        /* 不太懂这里为什么要减8 */
        tempValueOfHRRE = tempValueOfHRRE - 8;
        if (tempValueOfHRRE > 8)
        {
            for (uint8_t i = 0;  i < tempValueOfHRRE; i++)
            {
                // for every loop we double the value of 2
                valueOfAHBPre = valueOfAHBPre * 2;
            }
        }
        else if (tempValueOfHRRE == 8)
        {
             valueOfAHBPre = 2 ;
        }
        else
        {
            valueOfAHBPre = 1 ;
        }
        return (SYSTEM_HSE / valueOfAHBPre);
    }
    else if(pRCCHandle->RCC_Config.clockSource == PLL_CLOCK)
    {
        tempValueOfHRRE = 0 ;
        valueOfAHBPre = 0 ;
        
        
        //uint32_t valueOfAHBPre = 2;
        tempValueOfHRRE  = ((pRCCHandle->pRCC->CFGR & 0xF0) >> 4) ;
        
        // OPTIMISATION REQUIRED CONSOLIDATE THE IF STATMENT TO ONE IF STATEMENT
        if (pRCCHandle->RCC_Config.PLLSource == HSI_CLOCK)
        {
            /* get PLLCLK value*/
            tempValueOfPLLCLK = (SYSTEM_HSI / 2) * ((pRCCHandle->pRCC->CFGR &  0x00C30000) >>16);
            
            /*
            temp = ((( SYSTEM_HSI / (pRCCHandle->pRCC->PLLCFGR & 0x3F) ) * 		// divide by M
                            ((pRCCHandle->pRCC->PLLCFGR & 0x7FC0) >> 6))) /		// divide N
                            ((((pRCCHandle->pRCC->PLLCFGR & (0x30000)) >> 16)*2) + 2)  ;	// divide by P
            */
            
            if(tempValueOfHRRE >=12) 
            {
                valueOfAHBPre = 4 ;		// 8, 16, 64, 128, 256
            }
            if (tempValueOfHRRE > 8)
            {
                tempValueOfHRRE = tempValueOfHRRE - 8;
                for (uint8_t i = 0;  i < tempValueOfHRRE; i++)
                {
                    // for every loop we double the value of 2
                    valueOfAHBPre = valueOfAHBPre * 2;
                }
            }
            else if (tempValueOfHRRE == 8)
            {
                valueOfAHBPre = 2 ;
            }
            else
            {
                valueOfAHBPre = 1 ;
            }
            /* divide by AHB prescaler (HPRE) */ 
             return (tempValueOfPLLCLK / valueOfAHBPre);
           
        }
        else if (pRCCHandle->RCC_Config.PLLSource == HSE_CLOCK)
        {
            tempValueOfHRRE = 0 ;
            valueOfAHBPre = 0 ;
            tempValueOfPLLCLK = ((SYSTEM_HSE / 2) * ((pRCCHandle->pRCC->CFGR &  0x00C30000) >>16));
            /*
            temp = (((SYSTEM_HSE / (pRCCHandle->pRCC->PLLCFGR & 0x3F) ) * 		// divide by M
                           ((pRCCHandle->pRCC->PLLCFGR & 0x7FC0) >> 6))) /		// divide N
                           ((((pRCCHandle->pRCC->PLLCFGR & (0x30000)) >> 16)*2) + 2)  ;	// divide by P
            */
            
            if (tempValueOfHRRE >=12)
            {
                valueOfAHBPre = 4 ;		// 8 ,16 ,32,64, 128 , 256
            }
            if (tempValueOfHRRE > 8)
            {
                tempValueOfHRRE = tempValueOfHRRE - 8 ;
                for (uint8_t i = 0;  i < tempValueOfHRRE; i++)
                {
                    // for every loop we double the value of 2
                    valueOfAHBPre = valueOfAHBPre * 2;
                }
            }
            else if (tempValueOfHRRE == 8)
            {
                valueOfAHBPre = 2 ;
            }else
            {
                valueOfAHBPre = 1 ;
            }
            return (tempValueOfPLLCLK / valueOfAHBPre);// divide by AHB prescaler (HPRE)
        }
    }
    return 0; 
}

uint32_t GetAPB1Clock(RCC_Handle_t* pRCCHandle)
{
    uint16_t tempValueOfPPRE1 = 0 ;
    uint8_t valueOfAPB1Pre = 2 ;

    /* get PPRE1 Value */
    tempValueOfPPRE1  = ((pRCCHandle->pRCC->CFGR & 0x0380) >> 7);

    if (tempValueOfPPRE1 > 4)
    {
    tempValueOfPPRE1 = tempValueOfPPRE1 - 4;
    for (uint8_t i = 0;  i < tempValueOfPPRE1; i++)
    {
        // for every loop we double the value of 2
        valueOfAPB1Pre = valueOfAPB1Pre * 2;
    }
    }
    else if(tempValueOfPPRE1 == 4)
    {
        valueOfAPB1Pre = 2 ;
    }
    else 
    {
        valueOfAPB1Pre = 1 ;
    }

    return ( GetAHBClock(pRCCHandle) / valueOfAPB1Pre);
}

uint32_t GetAPB2Clock(RCC_Handle_t* pRCCHandle)
{
    uint16_t tempOfAPB2Pre = 0 ;
    uint8_t valueOfAPB2Pre = 2 ;

    /* get PPRE2 Value */
    tempOfAPB2Pre = ((pRCCHandle->pRCC->CFGR & 0xE000 ) >> 13);

     if (tempOfAPB2Pre > 4)
     {
        tempOfAPB2Pre = tempOfAPB2Pre - 4 ;
        for (uint8_t i = 0;  i < tempOfAPB2Pre; i++) 
        {
         // for every loop we double the value of 2
         valueOfAPB2Pre = valueOfAPB2Pre * 2;
        }
     }
     else if (tempOfAPB2Pre == 4)
     {
            valueOfAPB2Pre = 2 ;
     }
     else 
     {
         valueOfAPB2Pre = 1 ;
     }

    return ( getAHBClock(pRCCHandle) / valueOfAPB2Pre );
}





