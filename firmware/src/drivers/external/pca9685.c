/*
 * pca9685.c
 *
 *  Created on: May 3, 2017
 *      Author: Sreeyesh N S <sreeyeshns@gmail.com>
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <i2c.h>
#include <pca9685.h>

static i2c_write_fn __pca9685_i2c_write = NULL;
static i2c_read_fn  __pca9685_i2c_read = NULL;
static uint8_t __pca9685_initialized = false;

#if 0
static int8_t PCA9685_read_reg(uint8_t reg_addr_start, uint8_t reg_count, uint8_t *value)
{
    if(NULL == value)
        return -1;
    
    if(reg_count >= PCA9685_WR_BUFF_SIZE - 1)
        return -2;
    
    if(__pca9685_i2c_write(PCA9685_I2C_ADDR, &reg_addr_start, 1) != 1)
    {
        return -3;
    }

    if(__pca9685_i2c_read(PCA9685_I2C_ADDR, value, reg_count) != reg_count)
        return -4;
    return 0;
}
#endif

static int8_t PCA9685_write_reg(uint8_t reg_addr_start, uint8_t reg_count, uint8_t *value)
{
    uint8_t buff[PCA9685_WR_BUFF_SIZE];
    uint16_t count;
    uint8_t offset = 0;
    if(NULL == value)
        return -1;
    if(reg_count >= PCA9685_WR_BUFF_SIZE - 1)
        return -2;
    buff[offset++] = reg_addr_start;
    for(count = 0; count < reg_count; count++)
    {
        buff[offset++] = value[count];
    }

    if(__pca9685_i2c_write(PCA9685_I2C_ADDR, buff, offset) == offset)
        return 0;

    return -1;
}

void delay(uint32_t i)
{
    for(i = 0; i < 65535; i++);
}

int8_t PCA9685_init(i2c_write_fn i2c_write, i2c_read_fn i2c_read)
{
    uint8_t value;
    if(NULL == i2c_read || NULL == i2c_write)
    {
        return -1;
    }

    if(I2C0_init(I2C_MODE_MASTER, NULL))
    {
        return -2;
    }
    __pca9685_i2c_write = i2c_write;
    __pca9685_i2c_read  = i2c_read;

    value = 0b00110001;

    PCA9685_write_reg(PCA9685_REG_MODE1, 1, &value);
    delay(500);

    value = PCA9685_PRESCALE_50_HZ;
    PCA9685_write_reg(PCA9685_REG_PRESCALE, 1, &value);

    __pca9685_initialized = true;
    return 0;
}

int8_t PCA9685_set_duty_cycle(uint8_t channel, float duty_cycle)
{
    uint32_t off_count = 0;
    uint8_t buff[2];
    if(channel > PCA9685_PWM_CHANEL_MAX)
        return -1;
    if(!__pca9685_initialized)
        return -2;

    if(duty_cycle > 100)
    {
        duty_cycle = 100;
    }

    off_count = (PCA9685_COUNTER_RANGE * duty_cycle) / 100;
    buff[0] = off_count & 0xFF;
    buff[1] = (off_count >> 8) & 0x0F;
    PCA9685_write_reg(PCA9685_REG_LED_N_OFF_L(channel), 2, buff);
    return 0;
}
