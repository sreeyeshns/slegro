/*
 * servo.c
 *
 *  Created on: May 23, 2017
 *      Author: Sreeyesh N S <sreeyeshns@gmail.com>
 */
#include <stdint.h>
#include <i2c.h>
#include <pca9685.h>
#include <pwm.h>
#include <servo.h>

int8_t SRV_init()
{
    if(PCA9685_init(I2C0_write, I2C0_read))
    {
        return -1;
    }

    PWM_init();
    return 0;
}

int8_t SRV_set_angle(uint8_t servo_no, uint8_t angle)
{
    int8_t ret_val = 0;
    float duty_cycle = 0.0f;
    if( servo_no >= SRV_MAX)
        return -1;
    if(angle > SRV_ANGLE_MAX)
        return -2;

    duty_cycle = (angle / 180.0f) + 1.0f;

    switch(servo_no)
    {
#ifdef __GNUC__
        case SRV_0 ... SRV_15:
#else
        case SRV_0:
        case SRV_1:
        case SRV_2:
        case SRV_3:
        case SRV_4:
        case SRV_5:
        case SRV_6:
        case SRV_7:
        case SRV_8:
        case SRV_9:
        case SRV_10:
        case SRV_11:
        case SRV_12:
        case SRV_13:
        case SRV_14:
        case SRV_15:
#endif
        {
            ret_val = PCA9685_set_duty_cycle(servo_no, duty_cycle);
            break;
        }
#ifdef __GNUC__
        case SRV_16 ... SRV_19:
#else
        case SRV_16:
        case SRV_17:
        case SRV_18:
        case SRV_19:
#endif
        {
            ret_val = PWM_set_duty_cycle(servo_no - SRV_16, duty_cycle);
            PWM_start(servo_no - SRV_16);
            break;
        }
    }
    return ret_val;
}

int8_t SRV_stop(uint8_t servo_no)
{
    if( servo_no >= SRV_MAX)
        return -1;
    switch(servo_no)
    {
#ifdef __GNUC__
        case SRV_0 ... SRV_15:
#else
        case SRV_0:
        case SRV_1:
        case SRV_2:
        case SRV_3:
        case SRV_4:
        case SRV_5:
        case SRV_6:
        case SRV_7:
        case SRV_8:
        case SRV_9:
        case SRV_10:
        case SRV_11:
        case SRV_12:
        case SRV_13:
        case SRV_14:
        case SRV_15:
#endif
        {
            /*
             * TODO: Need to call API to stop PCA9685 channels.
             */
            break;
        }
#ifdef __GNUC__
        case SRV_16 ... SRV_19:
#else
        case SRV_16:
        case SRV_17:
        case SRV_18:
        case SRV_19:
#endif
        {
            PWM_stop(servo_no - SRV_16);
            break;
        }
    }
    return 0;
}
