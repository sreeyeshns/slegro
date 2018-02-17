/*
 * timer.h
 *
 *  Created on: Jun 11, 2017
 *      Author: Sreeyesh N S <sreeyeshns@gmail.com>
 */

#ifndef _TIMER_H
#define _TIMER_H
#include <stdint.h>
#define T0IR    (*(volatile uint32_t *) 0xE0004000)
#define T0TCR   (*(volatile uint32_t *) 0xE0004004)
#define T0TC    (*(volatile uint32_t *) 0xE0004008)
#define T0PR    (*(volatile uint32_t *) 0xE000400C)
#define T0PC    (*(volatile uint32_t *) 0xE0004010)
#define T0MCR   (*(volatile uint32_t *) 0xE0004014)
#define T0MR0   (*(volatile uint32_t *) 0xE0004018)
#define T0MR1   (*(volatile uint32_t *) 0xE000401C)
#define T0MR2   (*(volatile uint32_t *) 0xE0004020)
#define T0MR3   (*(volatile uint32_t *) 0xE0004024)
#define T0CCR   (*(volatile uint32_t *) 0xE0004028)
#define T0CR0   (*(volatile uint32_t *) 0xE000402C)
#define T0CR1   (*(volatile uint32_t *) 0xE0004030)
#define T0CR2   (*(volatile uint32_t *) 0xE0004034)
#define T0CR3   (*(volatile uint32_t *) 0xE0004038)
#define T0EMR   (*(volatile uint32_t *) 0xE000403C)
#define T0CTCR  (*(volatile uint32_t *) 0xE0004070)

#define T1IR    (*(volatile uint32_t *) 0xE0008000)
#define T1TCR   (*(volatile uint32_t *) 0xE0008004)
#define T1TC    (*(volatile uint32_t *) 0xE0008008)
#define T1PR    (*(volatile uint32_t *) 0xE000800C)
#define T1PC    (*(volatile uint32_t *) 0xE0008010)
#define T1MCR   (*(volatile uint32_t *) 0xE0008014)
#define T1MR0   (*(volatile uint32_t *) 0xE0008018)
#define T1MR1   (*(volatile uint32_t *) 0xE000801C)
#define T1MR2   (*(volatile uint32_t *) 0xE0008020)
#define T1MR3   (*(volatile uint32_t *) 0xE0008024)
#define T1CCR   (*(volatile uint32_t *) 0xE0008028)
#define T1CR0   (*(volatile uint32_t *) 0xE000802C)
#define T1CR1   (*(volatile uint32_t *) 0xE0008030)
#define T1CR2   (*(volatile uint32_t *) 0xE0008034)
#define T1CR3   (*(volatile uint32_t *) 0xE0008038)
#define T1EMR   (*(volatile uint32_t *) 0xE000803C)
#define T1CTCR  (*(volatile uint32_t *) 0xE0008070)

/*
 * Initializes timer1. Should be called before any delay APIs.
 */
void TMR1_init(void);

/*
 * Generates delay in microseconds.
 * delay : Delay in microseconds.
 */
void delay_us(uint32_t delay);

/*
 * Generates delay in milliseconds.
 * delay : Delay in milliseconds.
 */
void delay_ms(uint32_t delay);

/*
 * Generates delay in seconds.
 * delay : Delay in seconds.
 */
void delay_sec(uint32_t delay);

#endif /* _TIMER_H */
