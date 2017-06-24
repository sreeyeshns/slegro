#ifndef _PPL_H
#define _PPL_H
#include <stdint.h>

#define PLLCON  (*(volatile uint32_t *) 0xE01FC080)
#define PLLCFG  (*(volatile uint32_t *) 0xE01FC084)
#define PLLSTAT (*(const volatile uint32_t *) 0xE01FC088)
#define PLLFEED (*(volatile uint32_t *) 0xE01FC08C)

/*
 * Initializes the PLL module and multiplies the clock frequency so that
 * the CPU runs at 60Mhz
 */
void PLL_init(void);
#endif
