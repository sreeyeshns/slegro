/*
 * servo.h
 *
 *  Created on: May 23, 2017
 *      Author: Sreeyesh N S <sreeyeshns@gmail.com>
 */

#ifndef _SERVO_H
#define _SERVO_H

#include <stdint.h>

#define SRV_ANGLE_MAX       180

enum
{
    SRV_0,
    SRV_1,
    SRV_2,
    SRV_3,
    SRV_4,
    SRV_5,
    SRV_6,
    SRV_7,
    SRV_8,
    SRV_9,
    SRV_10,
    SRV_11,
    SRV_12,
    SRV_13,
    SRV_14,
    SRV_15,
    SRV_16,
    SRV_17,
    SRV_18,
    SRV_19,
    SRV_MAX
};

/*
 * Initialize servo motor PWM channels.
 */
extern int8_t SRV_init(void);

/*
 * Sets the angle of the servo motor.
 * servo_no : Servo motor number (0 - 19).
 * angle    : Servo motor rotation angle (0 - 180);
 */
extern int8_t SRV_set_angle(uint8_t servo_no, uint8_t angle);
/*
 * Stops servo motor PWM channel.
 * servo_no : Servo motor number (0 - 19).
 */
extern int8_t SRV_stop(uint8_t servo_no);

#endif /* SERVO_H_ */
