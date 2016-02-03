#include <gpio.h>
#include <i2c.h>
static unsigned char __i2c0_initialised = false;
static unsigned char __i2c0_mode = I2C_MODE_MASTER;
void init_I2C0(unsigned char mode)
{
	I2C0SCLL	= 0x4B;
	I2C0SCLH	= 0x4B;
	I2C0CONSET	= 0x40;
	__i2c_mode	= mode;
}

static bool I2C0_start()
{
	I2C0CONCLR	= STO;
	I2C0CONSET	= STA;
	while(!SI);
	if(I2C0STAT == 0x08)
}

s;tatic void I2C0_write_char(unsigned char ch)
{
}

void I2C0_write_str(char *str)
{
	if(__i2c0_mode == I2C_MODE_MASTER)
	{
		I2C0_start();
	}
}

