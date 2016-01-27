#include<pll.h>
#include<serial.h>
int main()
{
	init_pll();
	init_UART0();
	UART0_write_text("***I love Chithra***");
	return 0;
}

