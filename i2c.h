/*
 * Author: Sreeyesh N S<sreeyeshns@gmail.com>
 */
#ifndef _I2C_H
#define _I2C_H

#include <vic.h>
#include <stdint.h>

#define I2C_WR              0
#define I2C_RD              1

#define I2C_BIT_MASK_RD     0x01
#define I2C_BIT_MASK_WR     0xFE

/* I2C modes */
#define I2C_MODE_MASTER     0x01
#define I2C_MODE_MASTER_INT 0x02
#define I2C_MODE_SLAVE      0x03
#define I2C_MODE_SLAVE_INT  0x04

/* I2C operations */
#define I2C_OP_RD     0x00
#define I2C_OP_WR     0x01
#define I2C_OP_UN     0x02

/* I2C0 configuration registers */
#define I2C0CONSET  (*(volatile uint32_t *) 0xE001C000)
#define I2C0STAT    (*(const volatile uint32_t *) 0xE001C004)
#define I2C0DAT     (*(volatile uint32_t *) 0xE001C008)
#define I2C0ADR     (*(volatile uint32_t *) 0xE001C00C)
#define I2C0SCLH    (*(volatile uint32_t *) 0xE001C010)
#define I2C0SCLL    (*(volatile uint32_t *) 0xE001C014)
#define I2C0CONCLR  (*(volatile uint32_t *) 0xE001C018)

/* I2C0 configuration registers bits */

/* I2C0CONSET bits  */
#define AA      (0x04)
#define SI      (0x08)
#define STO     (0x10)
#define STA     (0x20)
#define I2EN    (0x40)

/* I2C0CONCLR bits  */
#define AAC     AA
#define SIC     SI
#define STAC    STA
#define I2ENC   I2EN

#define	I2C_ERROR_UNINITIALISED -1
#define	I2C_ERROR_TRANSMIT      -2

typedef enum
{
    I2C_STATE_UNINITIALIZED     = 0x00,
    I2C_STATE_INITIALIZED       = 0xF8,
    I2C_STATE_START_XMIT        = 0x08,
    I2C_STATE_SLA_W_XMIT_ACK    = 0x18,
    I2C_STATE_SLA_W_XMIT_NACK   = 0x20,
    I2C_STATE_DATA_XMIT_ACK     = 0x28,
    I2C_STATE_DATA_XMIT_NACK    = 0x30,
    I2C_STATE_SLA_R_XMIT_ACK    = 0x40,
    I2C_STATE_SLA_R_XMIT_NACK   = 0x48,
    I2C_STATE_DATA_REVC_ACK     = 0x50,
    I2C_STATE_DATA_REVC_NACK    = 0x58,
    I2C_STATE_ERROR             = 0xFE,
    I2C_STATE_DONE              = 0xFF
}i2c_state_t;

typedef int32_t (*i2c_write_fn)(uint8_t addr, const uint8_t *buff, uint32_t size);
typedef int32_t (*i2c_read_fn)(uint8_t addr, uint8_t *buff, uint32_t size);

/* IRQ interrupt handler for I2C0 */
extern void I2C0_IRQ_handler(void) __attribute__ ((interrupt("IRQ")));

/*
 * I2C initialization function. In mode with interrupt support handler should be a valid IRQ handler.
 * In other modes handler parameter is simply ignored. However it is recommended pass NULL in modes without interrupt support.
 */
extern int8_t I2C0_init(uint8_t mode, IRQ_handler handler);

/*
 * Routine to check whether I2C module is initialized or not.
 * Returns TRUE if module is initialized or FALSE otherwise.
 */
extern int8_t I2C0_is_initialized(void);

/*
 * I2C write function. Returns number of bytes read if the call is successful and returns a negative error code in case of failure.
 */
extern int32_t I2C0_read(uint8_t addr, uint8_t *buff, uint32_t buff_len);

/*
 * I2C write function. Returns number of bytes written if the call is successful and returns a negative error code in case of failure.
 */
extern int32_t I2C0_write(uint8_t addr, const uint8_t *buff, uint32_t buff_len);

#endif
