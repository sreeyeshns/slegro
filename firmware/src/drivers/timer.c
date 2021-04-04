/*
 * timer.c
 *
 *  Created on: Jun 11, 2017
 *      Author: Sreeyesh N. S. <sreeyeshns@gmail.com>
 */
#include <timer.h>
#include <system.h>
void TMR1_init()
{
    T1MCR |= 0x07U;
}

void delay_us(uint32_t delay)
{
    T1MR0 = delay;
    T1TC  = 0x00U;
    T1PC  = 0x00U;
    T1PR  = SYS_PCLK_MHZ;
    T1TCR = 0x01U;
    while(!(T1IR & 0x01U));
    T1IR &= 0x01U;
}

void delay_ms(uint32_t delay)
{
    T1MR0 = delay;
    T1TC  = 0x00U;
    T1PC  = 0x00U;
    T1PR  = SYS_PCLK_MHZ * 1000U;
    T1TCR = 0x01U;
    while(!(T1IR & 0x01U));
    T1IR &= 0x01U;
}
void delay_sec(uint32_t delay)
{
    T1MR0 = delay;
    T1TC  = 0x00U;
    T1PC  = 0x00U;
    T1PR  = SYS_PCLK_MHZ * 1000000U;
    T1TCR = 0x01U;
    while(!(T1IR & 0x01U));
    T1IR &= 0x01U;
}
