#include <gpio.h>
#include <i2c.h>
void init_I2C0()
{
	I2C0SCLL	= 0x4B
	I2C0SCLH	= 0x4B;
	I2C0ONSET	= 0x40;
}

void I2C0_write_char(unsigned char ch)
{
}
void I2C0_write_text(char *str)
{

}

