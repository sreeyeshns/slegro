/*
 * log.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Sreeyesh N.S. <sreeyeshns@gmail.com>
 */

#ifndef _LOG_H
#define _LOG_H
#include <stdint.h>

#define LOG_BUFF_SIZE   512

typedef void (*log_fn_t)(int8_t *);

extern void log_init(log_fn_t fn);
extern void sys_log(char *fmt, ...);

#endif /* _LOG_H */
