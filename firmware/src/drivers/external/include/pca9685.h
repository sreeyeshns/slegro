/*
 * pca9685.h
 *
 *  Created on: May 3, 2017
 *      Author: Sreeyesh N S <sreeyeshns@gmail.com>
 */

#ifndef _PCA9685_H
#define _PCA9685_H
#include <stdint.h>
#include <i2c.h>

#define PCA9685_REG_MODE1           0x00
#define PCA9685_REG_MODE2           0x01
#define PCA9685_REG_SUBADDR1        0x02
#define PCA9685_REG_SUBADDR2        0x03
#define PCA9685_REG_SUBADDR3        0x04
#define PCA9685_REG_ALLCALLADDR     0x05
#define PCA9685_REG_LEDX_ON_L       0x06
#define PCA9685_REG_LEDX_ON_H       0x07
#define PCA9685_REG_LEDX_OFF_L      0x08
#define PCA9685_REG_LEDX_OFF_H      0x09

#define PCA9685_REG_ALL_LED_ON_L    0xFA
#define PCA9685_REG_ALL_LED_ON_H    0xFB
#define PCA9685_REG_ALL_LED_OFF_L   0xFC
#define PCA9685_REG_ALL_LED_OFF_H   0xFD
#define PCA9685_REG_PRESCALE        0xFE

#define PCA9685_PRESCALE_MIN        0x03    /* => max. frequency of 1526 Hz */
#define PCA9685_PRESCALE_MAX        0xFF    /* => min. frequency of 24 Hz */

#define PCA9685_COUNTER_RANGE       4096

#define PCA9685_NUMREGS         0xFF
#define PCA9685_PWM_CHANEL_MAX  15

#define LED_FULL                (1 << 4)
#define MODE1_RESTART           (1 << 7)
#define MODE1_SLEEP             (1 << 4)
#define MODE2_INVRT             (1 << 4)
#define MODE2_OUTDRV            (1 << 2)

#define PCA9685_REG_LED_N_ON_H(N)           (PCA9685_REG_LEDX_ON_H + (4 * (N)))
#define PCA9685_REG_LED_N_ON_L(N)           (PCA9685_REG_LEDX_ON_L + (4 * (N)))
#define PCA9685_REG_LED_N_OFF_H(N)          (PCA9685_REG_LEDX_OFF_H + (4 * (N)))
#define PCA9685_REG_LED_N_OFF_L(N)          (PCA9685_REG_LEDX_OFF_L + (4 * (N)))

#define PCA9685_I2C_ADDR        0x8A
#define PCA9685_PRESCALE_50_HZ  0x79

#define PCA9685_RD_BUFF_SIZE    1
#define PCA9685_WR_BUFF_SIZE    256

/*
 * Initializes PCA9685 chip.
 * i2c_write: Function pointer to I2C write function.
 * i2c_read: Function pointer to I2C read function.
 */
extern int8_t PCA9685_init(i2c_write_fn i2c_write, i2c_read_fn i2c_read);

/*
 * Set the duty cycle of a PCA9685 PWM channel.
 * channel: Logical channel number (0 - 15).
 * duty_cycle: PWM duty cycle(0.0 - 100.0)
 */
extern int8_t PCA9685_set_duty_cycle(uint8_t channel, float duty_cycle);

#endif /* PCA9685_H_ */
