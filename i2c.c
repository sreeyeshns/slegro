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
	__i2c0_initialised = TRUE;
}

static bool I2C0_start()
{
	I2C0CONCLR	= 0xFF;
	I2C0CONSET	= STA;
	while(!SI);
	I2C0CONCLR	= STAC | SIC;
	
	if(I2C0STAT != 0x08)
	{
		return FALSE;
	}
	return TRUE;
}
static void I2C0_stop()
{
	I2C0CONSET = STO;
	while(!SI);
}

static inline bool I2C0_slave_addr(unsigned char addr, bool rw)
{
	addr = rw ? addr | BIT_MASK_RD : addr & BIT_MASK_WR;
	I2C0DAT = addr;
	while(!SI);
	//I2C0CONCLR	= STAC;
	if(I2C0STAT != 0x18)
		return FALSE;
	I2C0CONCLR	= STAC | SIC;
	return TRUE;
}

long I2C0_write(unsigned char addr, const char *buff, unsigned long buff_len)
{
	unsigned long count = 0;
	if(!__i2c0_initialised)
			return I2C_ERROR_UNINITIALISED;
	if(__i2c0_mode == I2C_MODE_MASTER)
	{
		I2C0_start();
		I2C0_slave_addr(addr, I2C_WR);
		for(count = 0; count < buff_len; count++)
		{
			I2C0DAT = *buff++;
			while(!SI);
			I2C0CONCLR	= STAC;
			if(I2C0STAT == 0x28)
			{
				continue;
			}
			else if(I2C0STAT == 0x30)
			{
				break;
			}
			else
			{
				return I2C_ERROR_TRANSMIT;
			}
		}
		I2C0_stop();
	}
	return count;
}

