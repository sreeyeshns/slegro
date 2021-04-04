/*
 * pwm.c
 *
 *  Created on: May 10, 2017
 *      Author: Sreeyesh N S <sreeyeshns@gmail.com>
 */
#include <stdint.h>
#include <stdbool.h>
#include <pwm.h>
#include <gpio.h>

static uint8_t __pwm_initialized = false;

void PWM_init()
{
    PINSEL0 |= 0x000A8000U;
    PINSEL1 |= 0x00000800U;
    PWMPR    = 0x00000048U;
    PWMMCR   = 0x00000002U;

    PWMMR0   = 0x00001000U;
    PWMMR2   = 0x00000000U;
    PWMMR4   = 0x00000000U;
    PWMMR5   = 0x00000000U;
    PWMMR6   = 0x00000000U;

    PWMLER   = 0x00000074U;
    PWMTCR   = 0x00000002U;
    PWMTCR   = 0x00000009U;
    __pwm_initialized = true;
}

int8_t PWM_set_duty_cycle(uint8_t channel, float duty_cycle)
{
    uint32_t off_count = 0;
    if(channel >= PWM_CHANNEL_MAX)
        return -1;
    if(!__pwm_initialized)
        return -2;

    if(duty_cycle > 100.0f)
    {
        duty_cycle = 100.0f;
    }

    off_count = (PWM_COUNTER_RANGE * duty_cycle) / 100;
    switch(channel)
    {
        case PWM_CHANNEL_0:
        {
            PWMMR2 = off_count;
            break;
        }
        case PWM_CHANNEL_1:
        {
            PWMMR4 = off_count;
            break;
        }
        case PWM_CHANNEL_2:
        {
            PWMMR5 = off_count;
            break;
        }
        case PWM_CHANNEL_3:
        {
            PWMMR6 = off_count;
            break;
        }
    }
    return 0;
}

int8_t PWM_start(uint8_t channel)
{
    if(channel >= PWM_CHANNEL_MAX)
        return -1;
    if(!__pwm_initialized)
        return -2;
    switch(channel)
    {
        case PWM_CHANNEL_0:
        {
            PWMPCR |= (0x00000001 << 10);
            break;
        }
        case PWM_CHANNEL_1:
        {
            PWMPCR |= (0x00000001 << 12);
            break;
        }
        case PWM_CHANNEL_2:
        {
            PWMPCR |= (0x00000001 << 13);
            break;
        }
        case PWM_CHANNEL_3:
        {
            PWMPCR |= (0x00000001 << 14);
            break;
        }
    }
    return 0;
}

int8_t PWM_stop(uint8_t channel)
{
    if(channel >= PWM_CHANNEL_MAX)
        return -1;
    if(!__pwm_initialized)
        return -2;
    switch(channel)
    {
        case PWM_CHANNEL_0:
        {
            PWMPCR &= ~(0x00000001 << 10);
            break;
        }
        case PWM_CHANNEL_1:
        {
            PWMPCR &= ~(0x00000001 << 12);
            break;
        }
        case PWM_CHANNEL_2:
        {
            PWMPCR &= ~(0x00000001 << 13);
            break;
        }
        case PWM_CHANNEL_3:
        {
            PWMPCR &= ~(0x00000001 << 14);
            break;
        }
    }
    return 0;
}
