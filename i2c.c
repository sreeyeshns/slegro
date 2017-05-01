/*
 * Author      : Sreeyesh N S<sreeyeshns@gmail.com>
 * Description : I2C driver for LPC2138. Currently only I2C master transmit and master receive modes are supported.
 *               Capable of operating in polling and interrupt mode.
 */
#include <defs.h>
#include <gpio.h>
#include <i2c.h>
#include <vic.h>
#include <serial.h>
#include <stdio.h>
static uint8_t      __i2c0_initialised = FALSE;
static uint8_t      __i2c0_mode = I2C_MODE_MASTER;
static i2c_state_t  __i2C0_state = I2C_STATE_UNINITIALIZED;
static uint8_t      __i2c0_addr = 0;
static uint8_t      *__i2c0_buff = NULL;
static uint32_t     __i2c0_buff_size = 0;

extern uint8_t __vicinitialized;

int8_t I2C0_is_initialized()
{
    return __i2c0_initialised;
}

void I2C0_IRQ_handler(void)
{
    switch (I2C0STAT)
    {
        case I2C_STATE_START_XMIT:
        {
            I2C0DAT = __i2c0_addr ;
            I2C0CONCLR = STAC;
            __i2C0_state = I2C_STATE_START_XMIT;
            break;
        }
        case I2C_STATE_SLA_W_XMIT_ACK:
        case I2C_STATE_DATA_XMIT_ACK:
        {
            __i2C0_state = I2C0STAT;

            if (!(__i2c0_buff_size--))
            {
                __i2C0_state = I2C_STATE_DONE;
                I2C0CONSET = STO;
                while (I2C0CONSET & STO);
                __i2c0_buff_size = 0;
                break;
            }
            else
            {
                I2C0DAT = *__i2c0_buff++;
            }
            break;
        }
        case I2C_STATE_SLA_R_XMIT_ACK:
        {
            if(__i2c0_buff_size == 1)
                I2C0CONCLR = AAC;
            else
                I2C0CONSET = AA;
            break;
        }
        case I2C_STATE_DATA_REVC_ACK:
        case I2C_STATE_DATA_REVC_NACK:
        {
            if (!(__i2c0_buff_size--))
            {
                __i2C0_state = I2C_STATE_DONE;
                I2C0CONSET = STO;
                while (I2C0CONSET & STO);
                __i2c0_buff_size = 0;
                break;
            }
            else
            {
                *__i2c0_buff++ = I2C0DAT;
                if(__i2c0_buff_size == 1)
                    I2C0CONCLR = AAC;
            }
            break;
        }
        case I2C_STATE_SLA_W_XMIT_NACK:
        case I2C_STATE_SLA_R_XMIT_NACK:
            __i2C0_state = I2C_STATE_ERROR;
            break;
    }
    VICVectAddr = 0;
    I2C0CONCLR = SIC;
}

int8_t I2C0_init(uint8_t mode, IRQ_handler handler)
{
    if((mode == I2C_MODE_MASTER_INT || mode == I2C_MODE_MASTER_INT) && handler == NULL)
        return -1;
    PINSEL0 = 0x50;
    IO0DIR = 0x0C;
    IO0SET = 0x0C;

    I2C0CONCLR = AAC | SIC | STAC | I2ENC;
    I2C0SCLL = 0x4B;
    I2C0SCLH = 0x4B;
    if (__vicinitialized && ((mode == I2C_MODE_MASTER_INT) || (mode == I2C_MODE_MASTER_INT)) && handler != NULL)
    {
        VIC_install_IRQ(INT_NUM_I2C0, I2C0_IRQ_handler, NULL);
    }
    I2C0CONSET = I2EN;
    __i2c0_mode = mode;
    __i2c0_initialised = TRUE;
    __i2C0_state = I2C_STATE_INITIALIZED;
    return 0;
}

static inline uint8_t I2C0_start()
{
    I2C0CONCLR = SIC;
    I2C0CONSET = STA;
    if (__i2c0_mode == I2C_MODE_MASTER)
    {
        while (!(I2C0CONSET & SI));
        if (I2C0STAT != I2C_STATE_START_XMIT)
        {
            return FALSE;
        }
        else
        {
            I2C0CONCLR = STAC;
        }
    }
    else if (__i2c0_mode == I2C_MODE_MASTER_INT)
    {
        while (__i2C0_state != I2C_STATE_START_XMIT);
    }
    return TRUE;
}

static void I2C0_stop()
{
    I2C0CONSET = STO;
    while (I2C0CONSET & STO);
}

static inline int8_t I2C0_slave_addr(uint8_t addr, bool rw)
{
    addr = rw ? addr | I2C_BIT_MASK_RD : addr & I2C_BIT_MASK_WR;
    I2C0DAT = addr;
    I2C0CONCLR = SIC;
    while (!(I2C0CONSET & SI));

    switch (I2C0STAT)
    {
        case I2C_STATE_SLA_W_XMIT_ACK:
        {
            if(rw == I2C_WR)
                return TRUE;
            else
                return FALSE;
        }
        case I2C_STATE_SLA_R_XMIT_ACK:
        {
            if(rw == I2C_RD)
                return TRUE;
            else
                return FALSE;
        }
        case I2C_STATE_SLA_W_XMIT_NACK:
        case I2C_STATE_SLA_R_XMIT_NACK:
        default:
            return FALSE;
    }
}

int32_t I2C0_write(uint8_t addr, const uint8_t *buff, uint32_t buff_len)
{
    uint32_t count = 0;
    if (!__i2c0_initialised)
        return I2C_ERROR_UNINITIALISED;
    if (!buff_len)
        return 0;
    if (__i2c0_mode == I2C_MODE_MASTER_INT)
    {
        addr = addr & I2C_BIT_MASK_WR;
        __i2c0_addr = addr;
        __i2c0_buff = (uint8_t *) buff;
        __i2c0_buff_size = buff_len;
    }
    if (I2C0_start() == FALSE)
    {
        return -2;
    }
    if (__i2c0_mode == I2C_MODE_MASTER_INT)
    {
        while (__i2C0_state != I2C_STATE_DONE && __i2C0_state != I2C_STATE_ERROR);
        return buff_len - __i2c0_buff_size;
    }
    else if (__i2c0_mode == I2C_MODE_MASTER)
    {
        I2C0_slave_addr(addr, I2C_WR);
        for (count = 0; count < buff_len; count++)
        {
            I2C0DAT = buff[count];
            I2C0CONCLR = SIC;
            while (!(I2C0CONSET & SI));
            if (I2C0STAT != I2C_STATE_DATA_XMIT_ACK)
            {
                return count;
            }
        }
        I2C0_stop();
    }
    return count;
}

int32_t I2C0_read(uint8_t addr, uint8_t *buff, uint32_t buff_len)
{
    uint32_t count = 0;
    if (!__i2c0_initialised)
        return I2C_ERROR_UNINITIALISED;
    if (!buff_len)
        return 0;
    if (buff == NULL)
        return -2;

    if (__i2c0_mode == I2C_MODE_MASTER_INT)
    {
        __i2c0_addr = addr | I2C_BIT_MASK_RD;
        __i2c0_buff = (uint8_t *) buff;
        __i2c0_buff_size = buff_len;
    }

    if (I2C0_start() == FALSE)
    {
        return -2;
    }

    if (__i2c0_mode == I2C_MODE_MASTER_INT)
    {
        while (__i2C0_state != I2C_STATE_DONE && __i2C0_state != I2C_STATE_ERROR);
        return buff_len - __i2c0_buff_size;
    }
    else if (__i2c0_mode == I2C_MODE_MASTER)
    {

        I2C0_slave_addr(addr, I2C_RD);

        if (buff_len > 1)
            I2C0CONSET = AA;

        for (count = 0; count < buff_len; count++)
        {
            if (count == buff_len - 1)
                I2C0CONCLR = AAC;

            I2C0CONCLR = SIC;
            while (!(I2C0CONSET & SI));
            if (I2C0STAT == I2C_STATE_DATA_REVC_ACK || I2C0STAT == I2C_STATE_DATA_REVC_NACK)
            {
                *buff++ = I2C0DAT;
                if(I2C0STAT == I2C_STATE_DATA_REVC_NACK)
                {
                    count++;
                    break;
                }
            }
            else
            {
                break;
            }
        }
        I2C0_stop();
    }
    return count;
}
