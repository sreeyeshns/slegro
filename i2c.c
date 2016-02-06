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

static bool I2C0_start(unsigned char addr, bool rw)
{
	I2C0CONCLR	= STO;
	I2C0CONSET	= STA;
	while(!SI);
	I2C0CONCLR	= STAC;
	if(I2C0STAT != 0x08)
	{
		return FALSE;
	}
	addr = rw ? addr & 0x01 : addr | 0xFE;
	I2C0DAT = addr;

	return TRUE;
}

static void I2C0_write_char(unsigned char addr, unsigned char ch)
{
}

void I2C0_write_str(char *str)
{
	if(__i2c0_mode == I2C_MODE_MASTER)
	{
		I2C0_start();
	}
}

