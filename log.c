/*
 * log.c
 *
 *  Created on: Oct 8, 2017
 *      Author: Sreeyesh N. S. <sreeyeshns@gmail.com>
 */
#include <log.h>
#include <stdarg.h>
#include <stdio.h>

static log_fn_t log_fn = NULL;

void set_log_cb_fn(log_fn_t fn)
{
    log_fn = fn;
}

void sys_log(char *fmt, ...)
{
    int8_t log_buffer[LOG_BUFF_SIZE];
    va_list aptr;

    if(log_fn == NULL)
        return;

    va_start(aptr, fmt);
    vsnprintf((char *)log_buffer, LOG_BUFF_SIZE, fmt, aptr);
    va_end(aptr);
    log_fn(log_buffer);
}
