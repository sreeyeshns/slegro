#include <defs.h>
#include <gpio.h>
#include <i2c.h>
static unsigned char __i2c0_initialised = FALSE;
static unsigned char __i2c0_mode = I2C_MODE_MASTER;

void init_I2C0(unsigned char mode)
{
	I2C0SCLL	= 0x4B;
	I2C0SCLH	= 0x4B;
	I2C0CONSET	= I2EN;
	__i2c0_mode	= mode;
}

static bool I2C0_start()
{
	I2C0CONSET	= STA;
	while(!SI);
	I2C0CONCLR	= STAC;
	
	if(I2C0STAT != 0x08)
	{
		return FALSE;
	}
	return TRUE;
}
static bool I2C0_slave_addr(unsigned char addr, bool rw)
{
	addr = rw ? addr | BIT_MASK_RD : addr & BIT_MASK_WR;
	I2C0DAT = addr;
	return TRUE;
}

static void I2C0_write_byte(unsigned char addr, unsigned char ch)
{
}

unsigned long I2C0_write(unsigned char addr, const char *buff, unsigned long buff_len)
{
	if(__i2c0_mode == I2C_MODE_MASTER)
	{
		I2C0_start();
	}
	return 0;
}

