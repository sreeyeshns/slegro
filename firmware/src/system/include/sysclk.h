#ifndef _SYSCLK_H
#define _SYSCLK_H
#include <stdint.h>

#define RST_CLK_CTRL_BASE           0x40021000UL

#define RCC_CR                      (*(volatile uint32_t *)(RST_CLK_CTRL_BASE + 0x00))
#define RCC_CR_PLLRDY               0x02000000
#define RCC_CR_PLLON                0x01000000
#define RCC_CR_HSEON                0x00010000
#define RCC_CR_HSERDY               0x00020000

#define RCC_CFGR                    (*(volatile uint32_t *)(RST_CLK_CTRL_BASE + 0x04))
#define RCC_CFGR_PLLMUL_9           0x001C0000
#define RCC_CFGR_PLLSRC             0x00010000
#define RCC_CFGR_PPRE1_2            0x00000400
#define RCC_CFGR_SWS                0x0000000C
#define RCC_CFGR_SWS_PLL            0x00000008
#define RCC_CFGR_SW_PLL             0x00000002

#define RCC_APB2ENR                 (*(volatile uint32_t *)(RST_CLK_CTRL_BASE + 0x18))
#define RCC_APB2ENR_IOPAEN          0x00000004UL


/*
 * Initializes the PLL module and multiplies the clock frequency so that
 * the CPU runs at 72Mhz
 */
void sysclk_init(void);

#endif /* _SYSCLK_H */
