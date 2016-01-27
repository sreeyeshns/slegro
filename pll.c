#include <pll.h>

static void pll_feed()
{
	PLLFEED = 0xAA;
	PLLFEED = 0x55;
}

void init_pll()
{
	PLLCFG = 0x24;
	PLLCON = 0x01;
	pll_feed();
	while(!(PLLSTAT & 0x0400));

	PLLCON |= 0x03;
	pll_feed();
	while(!(PLLSTAT & 0x0400));
}
