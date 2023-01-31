/*
 * log.c
 *
 *  Created on: Oct 8, 2017
 *      Author: Sreeyesh N. S. <sreeyeshns@gmail.com>
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <log.h>

log_level_t g_log_level = LOG_INFO;

void log_message(const log_level_t level, const int8_t *func_name, const uint32_t line_num, const int8_t *fmt, ...)
{

   int8_t log_level_ch = 0;
   int8_t log_buff[LOG_BUFF_SIZE];
   uint8_t offset = 0;
   va_list aptr;
   switch(level)
   {
      case LOG_ERROR:
         log_level_ch = 'E';
         break;
      case LOG_WARNING:
         log_level_ch = 'W';
         break;
      case LOG_INFO:
         log_level_ch = 'I';
         break;
      case LOG_DEBUG:
         log_level_ch = 'D';
         break;
      default:
         log_level_ch = 'U';
         break;
   }

   offset = snprintf((char *)log_buff, LOG_BUFF_SIZE, "[%c] "
#ifdef DEBUG
      "%s():%ld - "
#endif
      ,log_level_ch
#ifdef DEBUG
      , func_name, line_num
#endif
      );
   va_start(aptr, fmt);
   vsnprintf((char *)log_buff + offset, LOG_BUFF_SIZE - offset, (char *)fmt, aptr);
   va_end(aptr);
   fprintf(stdout, "%s\r\n", log_buff);
   fflush(stdout);
}
