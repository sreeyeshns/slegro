/*
 * system.c
 *
 *  Created on: May 9, 2021
 *      Author: Sreeyesh Sreedharan<sreeyeshns@gmail.com>
 */

#include <serial.h>
#include <pll.h>

extern int32_t (*__console_write)(uint8_t *, uint32_t);

int32_t system_init()
{
    /* Initialize the PLL to set 25 MHZ clock */
    PLL_init();

    /* Initialize UART0 for console access */
    UART0_init(BAUD_RATE_9600, WORD_LENGTH_8, PARITY_NONE, STOP_BIT_1);

    /* Set the console write API */
    __console_write = UART0_write;

    return 0;
}

