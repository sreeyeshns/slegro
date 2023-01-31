/*
 * log.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Sreeyesh N.S. <sreeyeshns@gmail.com>
 */

#ifndef _LOG_H
#define _LOG_H

#include <stdint.h>

#define LOG_BUFF_SIZE 128

typedef enum
{
   LOG_DISABLED,
   LOG_ERROR,
   LOG_WARNING,
   LOG_INFO,
   LOG_DEBUG,
}log_level_t;

#define LOG_ERROR(args...)        if (LOG_ERROR    <= g_log_level) log_message(LOG_ERROR,    (int8_t *)__FUNCTION__, __LINE__, (int8_t *) args)
#define LOG_WARNING(args...)      if (LOG_WARNING  <= g_log_level) log_message(LOG_WARNING,  (int8_t *)__FUNCTION__, __LINE__, (int8_t *) args)
#define LOG_INFO(args...)         if (LOG_INFO     <= g_log_level) log_message(LOG_INFO,     (int8_t *)__FUNCTION__, __LINE__, (int8_t *) args)
#define LOG_DEBUG(args...)        if (LOG_DEBUG    <= g_log_level) log_message(LOG_DEBUG,    (int8_t *)__FUNCTION__, __LINE__, (int8_t *) args)

extern log_level_t g_log_level;

void log_message(const log_level_t level, const int8_t *func_name, const uint32_t line_num, const int8_t *fmt, ...);

#endif /* _LOG_H */
