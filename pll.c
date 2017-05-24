#include <pll.h>

static void PLL_feed()
{
	PLLFEED = 0xAA;
	PLLFEED = 0x55;
}

void PLL_init()
{
	PLLCFG = 0x24;
	PLLCON = 0x01;
	PLL_feed();
	while(!(PLLSTAT & 0x0400));

	PLLCON |= 0x03;
	PLL_feed();
	while(!(PLLSTAT & 0x0400));
}
