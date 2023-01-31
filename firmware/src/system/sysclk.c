#include <common.h>
#include <sysclk.h>

void sysclk_init(void)
{
    /* External oscillator = 8 Mhz and required SYSCLK = 72 Mhz */

    RCC.CR_HSEON = BIT_SET;
    while(!(RCC.CR_HSERDY));

    /* PLL multiplication factor = 9, PLL Source = HSE and APB1 pre-scalar = 2 */
    RCC.CFGR_PLLMUL = RCC_CFGR_PLLMUL_9;
    RCC.CFGR_PPRE1 = RCC_CFGR_PPRE1_2;
    RCC.CFGR_PLLSRC = RCC_CFGR_PLLSRC_HSE;

    /* Enable PLL and wait for lock */
    RCC.CR_PLLON = BIT_SET;
    while(!(RCC.CR_PLLRDY));

    /* Switch system clock source to PLL */
    RCC.CFGR_SW = RCC_CFGR_SW_PLL;
    while((RCC.CFGR_SWS) != RCC_CFGR_SW_PLL);
}
