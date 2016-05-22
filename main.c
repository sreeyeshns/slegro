#include <pll.h>
#include <serial.h>
#include <i2c.h>
#include <vic.h>

void delay()
{
	unsigned long i;
	for(i = 0; i < 0xFFFFF; i++);
}

int main()
{
	char ch = 'a';
	init_pll();
	init_UART0();
	//printf("Hello");
	delay();
	//UART0_write_text("***I love Chithra***");
	VIC_init();
	I2C0_init(I2C_MODE_MASTER);
	I2C0_write(0xA0, &ch, 1);
	while(1);

	return 0;
}

