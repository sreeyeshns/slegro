#include <sysclk.h>

void sysclk_init(void)
{
    /* External oscillator = 8 Mhz and required SYSCLK = 72 Mhz */

    /* Enable High Speed External oscillator */
    RCC_CR |= RCC_CR_HSEON;
    while(!(RCC_CR & RCC_CR_HSERDY));

    /* PLL multiplication factor = 9, PLL Source = HSE and APB1 pre-scalar = 2 */
    RCC_CFGR |= RCC_CFGR_PLLMUL_9 | RCC_CFGR_PLLSRC | RCC_CFGR_PPRE1_2;

    /* Enable PLL and wait for lock */
    RCC_CR |= RCC_CR_PLLON;
    while(!(RCC_CR & RCC_CR_PLLRDY));

    /* Switch system clock source to PLL */
    RCC_CFGR |= RCC_CFGR_SW_PLL;
    while((RCC_CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
