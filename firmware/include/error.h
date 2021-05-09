/*
 * err.h
 *
 *  Created on: 01-May-2017
 *      Author: Sreeyesh N. S.<sreeyeshns@gmail.com>
 */

#ifndef ERR_H_
#define ERR_H_

typedef enum
{
   ERROR_NONE,
   ERROR_UART_INIT,
   ERROR_UART_WRITE,
   ERROR_UART_READ
}ret_code_t;

#endif /* ERR_H_ */
