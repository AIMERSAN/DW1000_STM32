/*! ----------------------------------------------------------------------------
 * @file    deca_sleep.c
 * @brief   platform dependent sleep implementation
 *
 * @attention
 *
 * Copyright 2015 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */

#include "deca_sleep.h"
#include "bsp_DWM1000.h"

/* 为什么芯片睡眠要这么设置, 在中断中声明一个计数变量 */
void deca_sleep(unsigned int time_ms)
{
    /* This assumes that the tick has a period of exactly one millisecond. See CLOCKS_PER_SEC define. */
    unsigned long end = getTickCount() + time_ms;
    while ((signed long)(getTickCount() - end) <= 0);
}
