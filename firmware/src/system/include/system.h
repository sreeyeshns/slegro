#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <serial.h>
#define SERIAL_CHANNEL_CONSOLE          SERIAL_CHANNEL1
#define ConsoleWrite(Data, DataLen)     SerialSendData(SERIAL_CHANNEL_CONSOLE, Data, DataLen)

#endif //_SYSTEM_H
