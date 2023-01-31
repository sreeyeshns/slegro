#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <serial.h>
#define SERIAL_CHANNEL_CONSOLE          SERIAL_CHANNEL1
#define console_write(data, data_len)   serial_send_data(SERIAL_CHANNEL_CONSOLE,data, data_len)

#endif //_SYSTEM_H
