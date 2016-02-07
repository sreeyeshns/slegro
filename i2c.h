#ifndef _I2C_H
#define _I2C_H

#define	BIT_MASK_RD	0x01
#define	BIT_MASK_WR	0xFE

/* I2C modes */
#define I2C_MODE_MASTER		0
#define I2C_MODE_SLAVE		1

/* I2C0 configuration registers */
#define I2C0CONSET	(*(volatile unsigned char *) 0xE001C000)
#define I2C0STAT	(*(volatile unsigned char *) 0xE001C004)
#define I2C0DAT		(*(volatile unsigned char *) 0xE001C008)
#define I2C0ADR		(*(volatile unsigned char *) 0xE001C00C)
#define I2C0SCLH	(*(volatile unsigned char *) 0xE001C010)
#define I2C0SCLL	(*(volatile unsigned char *) 0xE001C014)
#define I2C0CONCLR	(*(volatile unsigned char *) 0xE001C018)

/* I2C0 configuration registers bits */

/* I2C0CONSET bits  */
#define	AA	(0x04)
#define	SI	(0x08)
#define	STO	(0x10)
#define	STA	(0x20)
#define	I2EN	(0x40)

/* I2C0CONCLR bits  */
#define	AAC	AA  
#define	SIC	SI  
#define	STOC	STO 
#define	STAC	STA 
#define	I2ENC	I2EN

extern void init_I2C0(unsigned char mode);
unsigned long I2C0_read(unsigned char addr, char *buff, unsigned long buff_len);
unsigned long I2C0_write(unsigned char addr, const char *buff, unsigned long buff_len);

#endif
