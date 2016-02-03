#ifndef _I2C_H
#define _I2C_H

#define I2C_MODE_MASTER		0
#define I2C_MODE_SLAVE		1

#define I2C0SCLL	(*(volatile unsigned char *) 0xE000C014)
#define I2C0SCLH	(*(volatile unsigned char *) 0xE001C010)

void init_I2C0(void);
extern unsigned char I2C0_read(void);
extern void I2C0_write_char(unsigned char ch);
extern void I2C0_write_text(char *str);

#endif
