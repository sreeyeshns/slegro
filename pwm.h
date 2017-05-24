/*
 * pwm.h
 *
 *  Created on: May 10, 2017
 *      Author: Sreeyesh N S <sreeyeshns@gmail.com>
 */

#ifndef _PWM_H
#define _PWM_H

#include <stdint.h>

#define PWMIR   (*(volatile unsigned long *) 0xE0014000)
#define PWMTCR  (*(volatile unsigned long *) 0xE0014004)
#define PWMTC   (*(volatile unsigned long *) 0xE0014008)
#define PWMPR   (*(volatile unsigned long *) 0xE001400C)
#define PWMPC   (*(volatile unsigned long *) 0xE0014010)
#define PWMMCR  (*(volatile unsigned long *) 0xE0014014)
#define PWMMR0  (*(volatile unsigned long *) 0xE0014018)
#define PWMMR1  (*(volatile unsigned long *) 0xE001401C)
#define PWMMR2  (*(volatile unsigned long *) 0xE0014020)
#define PWMMR3  (*(volatile unsigned long *) 0xE0014024)
#define PWMMR4  (*(volatile unsigned long *) 0xE0014040)
#define PWMMR5  (*(volatile unsigned long *) 0xE0014044)
#define PWMMR6  (*(volatile unsigned long *) 0xE0014048)
#define PWMPCR  (*(volatile unsigned long *) 0xE001404C)
#define PWMLER  (*(volatile unsigned long *) 0xE0014050)

#define PWM_COUNTER_RANGE       4096

/*
 *  PWM logical channel numbers. Some channels are not used
 *  since the pins allotted for functions.
 */
enum
{
    PWM_CHANNEL_0, /* PWM2 */
    PWM_CHANNEL_1, /* PWM4 */
    PWM_CHANNEL_2, /* PWM5 */
    PWM_CHANNEL_3, /* PWM6 */
    PWM_CHANNEL_MAX
};

/*
 * Initializes internal PWM module.
 */
extern void PWM_init(void);

/*
 * Set the duty cycle of a PWM channel.
 * channel: Logical channel number (PWM_CHANNEL_0 - PWM_CHANNEL_3).
 * duty_cycle: PWM duty cycle(0.0 - 100.0)
 */
extern int8_t PWM_set_duty_cycle(uint8_t channel, float duty_cycle);

/*
 * Starts PWM.
 * channel: Logical channel number (PWM_CHANNEL_0 - PWM_CHANNEL_3).
 */
extern int8_t PWM_start(uint8_t channel);

/*
 * Stops PWM.
 * channel: Logical channel number (PWM_CHANNEL_0 - PWM_CHANNEL_3).
 */
extern int8_t PWM_stop(uint8_t channel);

#endif /* _PWM_H */
